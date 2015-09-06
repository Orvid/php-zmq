/*
+----------------------------------------------------------------------+
| HipHop for PHP                                                       |
+----------------------------------------------------------------------+
| Copyright (c) 2010-2015 Facebook, Inc. (http://www.facebook.com)     |
| Copyright (c) 1997-2010 The PHP Group                                |
+----------------------------------------------------------------------+
| This source file is subject to version 3.01 of the PHP license,      |
| that is bundled with this package in the file LICENSE, and is        |
| available through the world-wide-web at the following url:           |
| http://www.php.net/license/3_01.txt                                  |
| If you did not receive a copy of the PHP license and are unable to   |
| obtain it through the world-wide-web, please send a note to          |
| license@php.net so we can mail you a copy immediately.               |
+----------------------------------------------------------------------+
*/
#include "ext_zmq.h"
#include "ext_zmq-private.h"

#include <mutex>

#include <time.h>
#ifdef __APPLE__
# include <mach/mach_time.h>
#elif !defined(_MSC_VER)
# include <sys/time.h>
#endif

#include "hphp/runtime/base/array-init.h"
#include "hphp/runtime/base/execution-context.h"
#include "hphp/runtime/vm/native-data.h"
#include "hphp/runtime/vm/vm-regs.h"
#include "hphp/runtime/ext/spl/ext_spl.h"

#include "tbb/concurrent_unordered_map.h"

namespace HPHP {

namespace zmq {

static Object createObject(Class* cls) {
  return Object::attach(g_context->createObject(cls, init_null(), false));
}

static Object createAndConstruct(Class* cls, const Variant& args) {
  Object inst{ cls };
  TypedValue ret;
  g_context->invokeFunc(&ret, cls->getCtor(), args, inst.get());
  tvRefcountedDecRef(&ret);
  return inst;
}

[[noreturn]]
void throwExceptionClass(Class* cls, const Variant& msg, const Variant& code) {
  throw createAndConstruct(cls, make_packed_array(msg, code));
}

[[noreturn]]
void throwExceptionClassZMQErr(Class* cls, std::string msg, int err) {
  throwExceptionClass(cls,
    folly::format(msg, zmq_strerror(err)).str(),
    err
  );
}

Class* s_ZMQContextClass;
Class* s_ZMQSocketClass;
Class* s_ZMQExceptionClass;
Class* s_ZMQContextExceptionClass;
Class* s_ZMQDeviceExceptionClass;
Class* s_ZMQPollExceptionClass;
Class* s_ZMQSocketExceptionClass;

static const StaticString
  s_ZMQContext("ZMQContext"),
  s_ZMQSocket("ZMQSocket"),

  s_ZMQException("ZMQException"),
  s_ZMQContextException("ZMQContextException"),
  s_ZMQDeviceException("ZMQDeviceException"),
  s_ZMQPollException("ZMQPollException"),
  s_ZMQSocketException("ZMQSocketException");

void ZMQExtension::initializeExceptionReferences() {
  s_ZMQContextClass = NamedEntity::get(s_ZMQContext.get())->clsList();
  s_ZMQSocketClass = NamedEntity::get(s_ZMQSocket.get())->clsList();
  s_ZMQExceptionClass = NamedEntity::get(s_ZMQException.get())->clsList();
  s_ZMQContextExceptionClass = NamedEntity::get(s_ZMQContextException.get())->clsList();
  s_ZMQSocketExceptionClass = NamedEntity::get(s_ZMQSocketException.get())->clsList();
  s_ZMQPollExceptionClass = NamedEntity::get(s_ZMQPollException.get())->clsList();
  s_ZMQDeviceExceptionClass = NamedEntity::get(s_ZMQDeviceException.get())->clsList();
}

///////////////////////////////////////////////////////////////////////////////

static ZMQExtension s_zmq_extension;
HHVM_GET_MODULE(zmq);

///////////////////////////////////////////////////////////////////////////////
// ZMQ
///////////////////////////////////////////////////////////////////////////////

#ifdef __APPLE__
static uint64_t s_scaling_factor;
#elif defined(_MSC_VER)
static int s_wrap_count;
static uint64_t s_last_ticks;
#endif

void ZMQ::initializeClock() {
#ifdef __APPLE__
  mach_timebase_info_data_t info;
  mach_timebase_info(&info);
  s_scaling_factor = info.numer / info.denom;
#endif
}

uint64_t ZMQ::clock() {
#ifdef __APPLE__
  return (mach_absolute_time() * s_scaling_factor) / 1000000;
#elif defined(_MSC_VER)
  uint64_t ticks = (uint64_t)GetTickCount();
  if (ticks < s_last_ticks) {
    static Mutex mutex;
    mutex.lock();
    if (ticks < s_last_ticks) {
      s_last_ticks = ticks;
      s_wrap_count++;
    }
    mutex.unlock();
  }

  ticks += (uint64_t)s_wrap_count * (uint64_t)MAXDWORD;
  return ticks;
#else
  struct timespec ts;
#if defined(CLOCK_MONOTONIC_RAW)
  if (clock_gettime(CLOCK_MONOTONIC_RAW, &ts) == 0) {
#else
  if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0) {
#endif
    return (uint64_t)(((uint64_t)ts.tv_sec * 1000) + ((uint64_t)ts.tv_nsec / 1000000));
  }

  struct timeval tv;
  gettimeofday(&tv, nullptr);
  return (uint64_t)(((uint64_t)tv.tv_sec * 1000) + ((uint64_t)tv.tv_usec / 1000));
#endif
}

int64_t HHVM_STATIC_METHOD(ZMQ, clock) {
  return ZMQ::clock();
}

#define PHP_ZMQ_VERSION_LEN 24
String ZMQ::getLibVersion() {
  char buffer[PHP_ZMQ_VERSION_LEN];
  int major = 0, minor = 0, patch = 0;
  zmq_version(&major, &minor, &patch);
  int len = snprintf(buffer, PHP_ZMQ_VERSION_LEN - 1, "%d.%d.%d", major, minor, patch);
  return String(buffer, len, CopyString);
}

///////////////////////////////////////////////////////////////////////////////
// ZMQContextData
///////////////////////////////////////////////////////////////////////////////

ZMQContextData::ZMQContextData(int ioThreads, bool isPersistent, bool isGlobal) :
  io_threads(ioThreads),
  is_persistent(isPersistent),
  is_global(isGlobal),
  pid(getpid()) {

  if (is_global) {
    static std::once_flag flag;
    static void* globalContext;
    std::call_once(flag, [&] {
      globalContext = zmq_init(io_threads);
    });
    z_ctx = globalContext;
  } else {
    z_ctx = zmq_init(io_threads);
  }

  if (!z_ctx) {
    throwExceptionClassZMQErr(s_ZMQContextExceptionClass, "Error creating context: {}", errno);
  }
}

static tbb::concurrent_unordered_map<int64_t, ZMQContextData*> s_persistent_context_list;
ZMQContextData* ZMQContextData::get(int64_t io_threads, bool is_persistent, bool is_global) {
  if (is_persistent && !is_global) {
    auto ct = s_persistent_context_list.find(io_threads);
    if (ct != s_persistent_context_list.end()) {
      return ct->second;
    }
  }

  auto ctx = new ZMQContextData(io_threads, is_persistent, is_global);
  if (is_persistent && !is_global) {
    s_persistent_context_list[io_threads] = ctx;
  }
  return ctx;
}

///////////////////////////////////////////////////////////////////////////////
// ZMQContext
///////////////////////////////////////////////////////////////////////////////

void HHVM_METHOD(ZMQContext, __construct, int64_t io_threads, bool is_persistent) {
  auto cont = Native::data<ZMQContext>(this_);
  cont->context = ZMQContextData::get(io_threads, is_persistent, false);
}

Object HHVM_STATIC_METHOD(ZMQContext, acquire) {
  auto obj = createObject(s_ZMQContextClass);
  auto intern = Native::data<ZMQContext>(obj);
  intern->context = ZMQContextData::get(1, true, true);
  return obj;
}

bool HHVM_METHOD(ZMQContext, isPersistent) {
  return Native::data<ZMQContext>(this_)->context->is_persistent;
}

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
int HHVM_METHOD(ZMQContext, getOpt, int64_t option) {
  auto ctx = Native::data<ZMQContext>(this_);
  
  if (option != ZMQ_MAX_SOCKETS) {
    throwExceptionClass(s_ZMQContextExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }

  int value = zmq_ctx_get(ctx->context->z_ctx, option);
  return value;
}

void HHVM_METHOD(ZMQContext, setOpt, int64_t option, int64_t value) {
  auto ctx = Native::data<ZMQContext>(this_);

  if (option != ZMQ_MAX_SOCKETS) {
    throwExceptionClass(s_ZMQContextExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }

  if (zmq_ctx_set(ctx->context->z_ctx, option, value) != 0) {
    throwExceptionClassZMQErr(s_ZMQContextExceptionClass, "Failed to set the option ZMQ::CTXOPT_MAX_SOCKETS value: {}", errno);
  }
}
#endif

Object HHVM_METHOD(ZMQContext, getSocket, int64_t type, const String& persistentId, const Variant& newSocketCallback) {
  return createAndConstruct(s_ZMQSocketClass, make_packed_array(Object(this_), type, persistentId, newSocketCallback));
}

///////////////////////////////////////////////////////////////////////////////
// ZMQSocketData
///////////////////////////////////////////////////////////////////////////////

ZMQSocketData::ZMQSocketData(ZMQContextData* ctx, int64_t type, bool isPersistent)
  : pid(getpid()), is_persistent(isPersistent) {
  z_socket = zmq_socket(ctx->z_ctx, type);
  if (!z_socket) {
    throwExceptionClassZMQErr(s_ZMQSocketExceptionClass, "Error creating socket: {}", errno);
  }
}

static tbb::concurrent_unordered_map<std::pair<int64_t, const char*>, ZMQSocketData*> s_persistent_socket_list;
ZMQSocketData* ZMQSocketData::get(ZMQContextData* ctx, int64_t type, const String& persistentId, bool& isNew) {
  bool isPersistent = ctx->is_persistent && !persistentId.isNull();
  if (isPersistent) {
    auto ct = s_persistent_socket_list.find(std::pair<int64_t, const char*>(type, persistentId.c_str()));
    if (ct != s_persistent_socket_list.end()) {
      isNew = false;
      return ct->second;
    }
  }

  isNew = true;
  auto dat = new ZMQSocketData(ctx, type, isPersistent);
  s_persistent_socket_list[std::pair<int64_t, const char*>(type, persistentId.c_str())] = dat;
  return dat;
}

///////////////////////////////////////////////////////////////////////////////
// ZMQSocket
///////////////////////////////////////////////////////////////////////////////

void HHVM_METHOD(ZMQSocket, __construct, const Object& context, int64_t type, const String& persistentId, const Variant& newSocketCallback) {
  auto sock = Native::data<ZMQSocket>(this_);
  auto ctx = Native::data<ZMQContext>(context);
  bool isNew = false;
  auto data = ZMQSocketData::get(ctx->context, type, persistentId, isNew);

  if (!data) {
    throwExceptionClassZMQErr(s_ZMQSocketExceptionClass, "Error creating socket: {}", errno);
  }

  sock->socket = data;
  if (!ctx->context->is_persistent) {
    sock->context_obj = context;
  }

  if (isNew) {
    if (!newSocketCallback.isNull()) {
      CallerFrame cf;
      CallCtx callCtx;
      vm_decode_function(newSocketCallback, cf(), false, callCtx, true);

      TypedValue ret;
      g_context->invokeFunc(&ret, callCtx, make_packed_array(Object(this_), persistentId));
      tvRefcountedDecRef(&ret);
    }
  }

  if (data->is_persistent) {
    sock->persistent_id = persistentId;
  }
}

bool ZMQSocket::send(const String& message_param, int64_t flags) {
  zmq_msg_t message;
  if (zmq_msg_init_size(&message, message_param.size()) != 0) {
    throwExceptionClassZMQErr(s_ZMQSocketExceptionClass, "Failed to initialize message structure: {}", errno);
  }
  memcpy(zmq_msg_data(&message), message_param.data(), message_param.size());

  int rc = zmq_sendmsg(socket->z_socket, &message, flags);
  int err = errno;

  zmq_msg_close(&message);

  if (rc == -1) {
    if (err == EAGAIN) {
      return false;
    }
    throwExceptionClassZMQErr(s_ZMQSocketExceptionClass, "Failed to send message: {}", err);
  }
  return true;
}

Variant HHVM_METHOD(ZMQSocket, send, const String& msg, int64_t flags) {
  auto ctx = Native::data<ZMQSocket>(this_);
  if (ctx->send(msg, flags))
    return Variant(this_);
  return false;
}

Variant HHVM_METHOD(ZMQSocket, sendMulti, const Array& messages, int64_t flags) {
  auto sock = Native::data<ZMQSocket>(this_);
  auto sz = messages.size();
  flags |= ZMQ_SNDMORE;
  for (auto i = 0; i < sz; i++) {
    if (i + 1 >= sz) {
      flags &= ~ZMQ_SNDMORE;
    }
    if (!sock->send(messages[i].toString(), flags))
      return false;
  }
  return Variant(this_);
}

bool ZMQSocket::recv(int64_t flags, String& msg) {
  zmq_msg_t message;
  if (zmq_msg_init(&message) != 0) {
    throwExceptionClassZMQErr(s_ZMQSocketExceptionClass, "Failed to initialize message structure: {}", errno);
  }

  int rc = zmq_recvmsg(socket->z_socket, &message, flags);
  int err = errno;

  if (rc == -1) {
    zmq_msg_close(&message);
    if (err == EAGAIN) {
      return false;
    }
    throwExceptionClassZMQErr(s_ZMQSocketExceptionClass, "Failed to recieve message: {}", err);
  }

  msg = String((char*)zmq_msg_data(&message), zmq_msg_size(&message), CopyString);
  zmq_msg_close(&message);
  return true;
}

Variant HHVM_METHOD(ZMQSocket, recv, int64_t flags) {
  auto sock = Native::data<ZMQSocket>(this_);
  String ret;
  if (sock->recv(flags, ret))
    return ret;
  return false;
}

Variant HHVM_METHOD(ZMQSocket, recvMulti, int64_t flags) {
  auto sock = Native::data<ZMQSocket>(this_);
#if ZMQ_VERSION_MAJOR < 3
  int64_t recvMoreVal;
#else
  int recvMoreVal;
#endif
  size_t recvMoreValLen = sizeof(recvMoreVal);

  PackedArrayInit ret(4);
  do {
    String msg;
    if (!sock->recv(flags, msg)) {
      return false;
    }
    ret.append(msg);
    zmq_getsockopt(sock->socket->z_socket, ZMQ_RCVMORE, &recvMoreVal, &recvMoreValLen);
  } while (recvMoreVal > 0);

  return ret.toArray();
}

Variant HHVM_METHOD(ZMQSocket, getPersistentId) {
  auto sock = Native::data<ZMQSocket>(this_);

  if (sock->socket->is_persistent && !sock->persistent_id.isNull()) {
    return sock->persistent_id;
  }
  return init_null();
}

Object HHVM_METHOD(ZMQSocket, bind, const String& dsn, bool force) {
  auto sock = Native::data<ZMQSocket>(this_);

  if (force || !sock->socket->bind.count(dsn)) {
    if (zmq_bind(sock->socket->z_socket, dsn.data()) != 0) {
      throwExceptionClassZMQErr(s_ZMQSocketExceptionClass, "Failed to bind the ZMQ: {}", errno);
    }
    sock->socket->bind.emplace(dsn);
  }
  return Object(Native::object(sock));
}

Object HHVM_METHOD(ZMQSocket, connect, const String& dsn, bool force) {
  auto sock = Native::data<ZMQSocket>(this_);

  if (force || !sock->socket->connect.count(dsn)) {
    if (zmq_connect(sock->socket->z_socket, dsn.data()) != 0) {
      throwExceptionClassZMQErr(s_ZMQSocketExceptionClass, "Failed to connect the ZMQ: {}", errno);
    }
    sock->socket->connect.emplace(dsn);
  }
  return Object(Native::object(sock));
}

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
Object HHVM_METHOD(ZMQSocket, unbind, const String& dsn) {
  auto sock = Native::data<ZMQSocket>(this_);

  if (zmq_unbind(sock->socket->z_socket, dsn.data()) != 0) {
    throwExceptionClassZMQErr(s_ZMQSocketExceptionClass, "Failed to unbind the ZMQ socket: {}", errno);
  }
  sock->socket->bind.erase(dsn);
  return Object(Native::object(sock));
}

Object HHVM_METHOD(ZMQSocket, disconnect, const String& dsn) {
  auto sock = Native::data<ZMQSocket>(this_);

  if (zmq_unbind(sock->socket->z_socket, dsn.data()) != 0) {
    throwExceptionClassZMQErr(s_ZMQSocketExceptionClass, "Failed to disconnect the ZMQ socket: {}", errno);
  }
  sock->socket->connect.erase(dsn);
  return Object(Native::object(sock));
}
#endif

static const StaticString
  s_connect("connect"),
  s_bind("bind");
Array HHVM_METHOD(ZMQSocket, getEndpoints) {
  auto sock = Native::data<ZMQSocket>(this_);

  PackedArrayInit bindPoints(sock->socket->bind.size());
  for (auto s : sock->socket->bind) {
    bindPoints.append(s);
  }
  PackedArrayInit connectPoints(sock->socket->connect.size());
  for (auto s : sock->socket->connect) {
    connectPoints.append(s);
  }

  Array ret = Array::Create();
  ret.add(s_bind, bindPoints.toVariant());
  ret.add(s_connect, connectPoints.toVariant());
  return ret;
}

int64_t HHVM_METHOD(ZMQSocket, getSocketType) {
  auto sock = Native::data<ZMQSocket>(this_);

  int type;
  size_t typeSize = sizeof(type);
  if (zmq_getsockopt(sock->socket->z_socket, ZMQ_TYPE, &type, &typeSize) != -1) {
    return type;
  }
  return -1;
}

bool HHVM_METHOD(ZMQSocket, isPersistent) {
  return Native::data<ZMQSocket>(this_)->socket->is_persistent;
}

///////////////////////////////////////////////////////////////////////////////
// ZMQPollData
///////////////////////////////////////////////////////////////////////////////

int ZMQPollData::add(const Variant& entry, int64_t events) {
  assert(php_items.size() == items.size());
  if (!entry.isObject() && !entry.isResource()) {
    return PHP_ZMQ_POLLSET_ERR_INVALID_TYPE;
  }

  auto key = ZMQPollData::createKey(entry);

  if (!key.length() || key.length() > 34) {
    return PHP_ZMQ_POLLSET_ERR_KEY_FAIL;
  }

  for (int i = 0; i < php_items.size(); i++) {
    if (php_items[i].key == key) {
      items[i].events = events;
      php_items[i].events = events;
      return i;
    }
  }

  if (entry.isResource()) {
    // TODO: Implement. I have no idea how to port this to HHVM...
    always_assert(false);
  } else {
    auto sock = Native::data<ZMQSocket>(entry.asCObjRef());
    zmq_pollitem_t item{};
    item.socket = sock->socket->z_socket;
    item.events = events;
    items.push_back(item);
  }

  // For resource, need to construct with file descriptor.
  php_items.push_back(ZMQPollItem(events, entry, key, items.back().socket));
  return items.size() - 1;
}

bool ZMQPollData::getKey(int pos, String& key) {
  if (pos < 0 || pos >= php_items.size()) {
    return false;
  }

  key = php_items[pos].key;
  return true;
}

bool ZMQPollData::erase(const Variant& entry) {
  return eraseByKey(createKey(entry));
}

bool ZMQPollData::eraseByKey(const String& key) {
  for (size_t i = 0; i < php_items.size(); i++) {
    if (php_items[i].key == key) {
      items.erase(items.begin() + i);
      php_items.erase(php_items.begin() + i);
      return true;
    }
  }
  return false;
}

void ZMQPollData::eraseAll() {
  items.clear();
  php_items.clear();
}

int ZMQPollData::poll(int64_t timeout, VRefParam readable, VRefParam writable) {
  errors.clear();

  auto rVar = readable.getVariantOrNull();
  Array rArr;
  if (rVar && rVar->isArray()) {
    rArr = rVar->asArrRef();
    rArr.clear();
  }

  auto wVar = writable.getVariantOrNull();
  Array wArr;
  if (wVar && wVar->isArray()) {
    wArr = wVar->asArrRef();
    wArr.clear();
  }

  assert(items.size() == php_items.size());

  int rc = zmq_poll(items.data(), items.size(), timeout);
  if (rc == -1) {
    return -1;
  }

  if (rc > 0) {
    for (size_t i = 0; i < items.size(); i++) {
      if (rVar && (items[i].revents & ZMQ_POLLIN)) {
        rArr.append(php_items[i].entry);
      }
      if (wVar && (items[i].revents & ZMQ_POLLIN)) {
        wArr.append(php_items[i].entry);
      }

      if (items[i].revents & ZMQ_POLLERR) {
        errors.append(php_items[i].key);
      }
    }
  }

  return rc;
}

String ZMQPollData::createKey(const Variant& val) {
  if (val.isResource()) {
    char tmp[35];
    int tmpLen = snprintf(tmp, 35, "r:%d", val.asCResRef().toInt32());
    return String(tmp, tmpLen, CopyString);
  } else {
    assert(val.isObject());
    return HHVM_FN(spl_object_hash)(val.asCObjRef());
  }
}

///////////////////////////////////////////////////////////////////////////////
// ZMQPoll
///////////////////////////////////////////////////////////////////////////////

String HHVM_METHOD(ZMQPoll, add, const Variant& obj, int64_t events) {
  auto poll = Native::data<ZMQPoll>(this_);

  switch (obj.getType()) {
    case DataType::KindOfObject:
      if (!obj.asCObjRef().instanceof(s_ZMQSocketClass)) {
        throwExceptionClass(s_ZMQPollExceptionClass, "The first argument must be an instance of ZMQSocket or a resource", PHP_ZMQ_INTERNAL_ERROR);
      }
      break;

    case DataType::KindOfResource:
      break;

    default:
      throwExceptionClass(s_ZMQPollExceptionClass, "The first argument must be an instance of ZMQSocket or a resource", PHP_ZMQ_INTERNAL_ERROR);
  }

  int pos = poll->set.add(obj, events);

  if (pos < 0) {
    const char* message = nullptr;

    switch (pos) {
      case PHP_ZMQ_POLLSET_ERR_NO_STREAM:
        message = "The supplied resource is not a valid stream resource";
        break;

      case PHP_ZMQ_POLLSET_ERR_CANNOT_CAST:
        message = "The supplied resource is not castable";
        break;

      case PHP_ZMQ_POLLSET_ERR_CAST_FAILED:
        message = "Failed to cast the supplied stream resource";
        break;

      case PHP_ZMQ_POLLSET_ERR_NO_INIT:
        message = "The ZMQSocket object has not been initialized properly";
        break;

      case PHP_ZMQ_POLLSET_ERR_NO_POLL:
        message = "The ZMQSocket object has not been initialized with polling";
        break;

      default:
        message = "Unknown error";
        break;
    }
    throwExceptionClass(s_ZMQPollExceptionClass, message, PHP_ZMQ_INTERNAL_ERROR);
  }

  String ret;
  if (!poll->set.getKey(pos, ret)) {
    throwExceptionClass(s_ZMQPollExceptionClass, "Failed to get the item key", PHP_ZMQ_INTERNAL_ERROR);
  }

  return ret;
}

bool HHVM_METHOD(ZMQPoll, remove, const Variant& item) {
  auto poll = Native::data<ZMQPoll>(this_);

  if (poll->set.items.size() == 0) {
    throwExceptionClass(s_ZMQPollExceptionClass, "No sockets assigned to the ZMQPoll", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (item.getType()) {
    case DataType::KindOfObject:
      if (!item.asCObjRef().instanceof(s_ZMQSocketClass)) {
        throwExceptionClass(s_ZMQPollExceptionClass, "The object must be an instance of ZMQSocket", PHP_ZMQ_INTERNAL_ERROR);
      }
    /* fallthrough */
    case DataType::KindOfResource:
      return poll->set.erase(item);

    default:
      return poll->set.eraseByKey(item.toString());
  }
}

int64_t HHVM_METHOD(ZMQPoll, poll, VRefParam readable, VRefParam writable, int64_t timeout) {
  auto poll = Native::data<ZMQPoll>(this_);

  if (poll->set.items.size() == 0) {
    throwExceptionClass(s_ZMQPollExceptionClass, "No sockets assigned to the ZMQPoll", PHP_ZMQ_INTERNAL_ERROR);
  }

  int rc = poll->set.poll(timeout * PHP_ZMQ_TIMEOUT, readable, writable);
  if (rc == -1) {
    throwExceptionClassZMQErr(s_ZMQPollExceptionClass, "Poll failed: {}", errno);
  }
  return rc;
}

int64_t HHVM_METHOD(ZMQPoll, count) {
  return Native::data<ZMQPoll>(this_)->set.items.size();
}

Object HHVM_METHOD(ZMQPoll, clear) {
  auto poll = Native::data<ZMQPoll>(this_);
  poll->set.eraseAll();
  return Object(Native::object(poll));
}

Array HHVM_METHOD(ZMQPoll, getLastErrors) {
  return Native::data<ZMQPoll>(this_)->set.errors;
}

///////////////////////////////////////////////////////////////////////////////
// ZMQDeviceCallback
///////////////////////////////////////////////////////////////////////////////

void ZMQDeviceCallback::clear() {
  if (initialized) {
    initialized = false;
    timeout = 0;
    callback = init_null();
    user_data = init_null();
    scheduled_at = 0;
  }
}

void ZMQDeviceCallback::assign(const Variant& cb, int64_t time, const Variant& ud) {
  initialized = true;
  user_data = Variant(ud);
  callback = Variant(cb);
  scheduled_at = ZMQ::clock() + time;
  timeout = time;
}

bool ZMQDeviceCallback::invoke(uint64_t currentTime) {
  CallerFrame cf;
  CallCtx ctx;
  vm_decode_function(callback, cf(), false, ctx, true);

  TypedValue ret;
  g_context->invokeFunc(&ret, ctx, make_packed_array(user_data));
  scheduled_at = currentTime + timeout;
  if (ret.m_type != DataType::KindOfUninit) {
    return cellToBool(ret);
  }
  tvRefcountedDecRef(&ret);
  return false;
}

///////////////////////////////////////////////////////////////////////////////
// ZMQDevice
///////////////////////////////////////////////////////////////////////////////

void HHVM_METHOD(ZMQDevice, __construct, const Object& frontend, const Object& backend, const Object& capture) {
  auto dev = Native::data<ZMQDevice>(this_);
  dev->front = Object(frontend);
  dev->back = Object(backend);
  dev->capture = Object(capture);
}

bool ZMQDevice::run() {
  zmq_msg_t msg;
  if (zmq_msg_init(&msg) != 0) {
    return false;
  }

  SCOPE_EXIT {
    int errno_ = errno;
    zmq_msg_close(&msg);
    errno = errno_;
  };

  zmq_pollitem_t items[2];
  items[0].socket = Native::data<ZMQSocket>(front)->socket->z_socket;
  items[0].fd = 0;
  items[0].events = ZMQ_POLLIN;
  items[0].revents = 0;
  items[1].socket = Native::data<ZMQSocket>(back)->socket->z_socket;
  items[1].fd = 0;
  items[1].events = ZMQ_POLLIN;
  items[1].revents = 0;

  void* captureSock = nullptr;
  if (!capture.isNull()) {
    captureSock = Native::data<ZMQSocket>(capture)->socket->z_socket;
  }

  uint64_t lastMessageReceived = ZMQ::clock();
  idle_cb.scheduled_at = lastMessageReceived + idle_cb.timeout;
  timer_cb.scheduled_at = lastMessageReceived + timer_cb.timeout;

  while (true) {
    int rc = zmq_poll(items, 2, calculateTimeout());
    if (rc < 0) {
      return false;
    }

    uint64_t currentTime = ZMQ::clock();
    if (rc > 0) {
      lastMessageReceived = currentTime;
    }

    if (timer_cb.initialized && timer_cb.timeout > 0) {
      if (timer_cb.scheduled_at <= currentTime) {
        if (!timer_cb.invoke(currentTime)) {
          return true;
        }
      }
    }

    if (rc == 0 && idle_cb.initialized && idle_cb.timeout > 0) {
      if ((currentTime - lastMessageReceived) >= idle_cb.timeout &&
          idle_cb.scheduled_at <= currentTime) {
        if (!idle_cb.invoke(currentTime)) {
          return true;
        }
      }
      continue;
    }

    if (items[0].revents & ZMQ_POLLIN) {
      if (!ZMQDevice::handleSocketRecieved(items[0].socket, items[1].socket, captureSock, &msg)) {
        return false;
      }
    }

    if (items[1].revents & ZMQ_POLLIN) {
      if (!ZMQDevice::handleSocketRecieved(items[1].socket, items[0].socket, captureSock, &msg)) {
        return false;
      }
    }
  }

  return false;
}

int ZMQDevice::calculateTimeout() {
  int timeout = -1;
  uint64_t current = ZMQ::clock();

  if (idle_cb.initialized && idle_cb.timeout) {
    timeout = (int)(idle_cb.scheduled_at - current);

    if (timeout <= 0) {
      return 1 * PHP_ZMQ_TIMEOUT;
    }
  }

  if (timer_cb.initialized && timer_cb.timeout) {
    int timerTimeout = (int)(timer_cb.scheduled_at - current);

    if (timerTimeout <= 0) {
      return 1 * PHP_ZMQ_TIMEOUT;
    }

    if (timeout == -1 || timerTimeout < timeout) {
      timeout = timerTimeout;
    }
  }

  if (timeout > 0) {
    timeout *= PHP_ZMQ_TIMEOUT;
  }

  return timeout;
}

bool ZMQDevice::handleSocketRecieved(void* sockA, void* sockB, void* captureSock, zmq_msg_t* msg) {
#if ZMQ_VERSION_MAJOR >= 3
  int more;
#else
  int64_t more;
#endif
  size_t moreSize = sizeof(more);

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0
  int label;
  size_t labelSize = sizeof(label);
#endif

  while (true) {
    if (zmq_recvmsg(sockA, msg, 0) == -1) {
      return false;
    }

    if (zmq_getsockopt(sockA, ZMQ_RCVMORE, &more, &moreSize) < 0) {
      return false;
    }

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0
    if (zmq_getsockopt(sockA, ZMQ_RCVLABEL, &label, &labelSize) < 0) {
      return false;
    }

    if (zmq_sendmsg(sockB, msg, label ? ZMQ_SNDLABEL : (more ? ZMQ_SNDMORE : 0)) == -1) {
      return false;
    }
    if (!more && !label) {
      break;
    }
#else
    if (captureSock) {
      zmq_msg_t msg_cp;
      if (zmq_msg_init(&msg_cp) == -1) {
        return false;
      }
      if (zmq_msg_copy(&msg_cp, msg) == -1) {
        zmq_msg_close(&msg_cp);
        return false;
      }
      if (zmq_sendmsg(captureSock, &msg_cp, more ? ZMQ_SNDMORE : 0) == -1) {
        zmq_msg_close(&msg_cp);
        return false;
      }
      zmq_msg_close(&msg_cp);
    }

    if (zmq_sendmsg(sockB, msg, more ? ZMQ_SNDMORE : 0) == -1) {
      return false;
    }

    if (!more) {
      break;
    }
#endif
  }
  return true;
}

void HHVM_METHOD(ZMQDevice, run) {
  if (!Native::data<ZMQDevice>(this_)->run()) {
    throwExceptionClassZMQErr(s_ZMQDeviceExceptionClass, "Failed to start the device: {}", errno);
  }
}

int64_t HHVM_METHOD(ZMQDevice, getIdleTimeout) {
  auto dev = Native::data<ZMQDevice>(this_);
  return dev->idle_cb.timeout;
}

Object HHVM_METHOD(ZMQDevice, setIdleTimeout, int64_t milliseconds) {
  auto dev = Native::data<ZMQDevice>(this_);
  dev->idle_cb.timeout = milliseconds;
  return Object(Native::object(dev));
}

int64_t HHVM_METHOD(ZMQDevice, getTimerTimeout) {
  auto dev = Native::data<ZMQDevice>(this_);
  return dev->timer_cb.timeout;
}

Object HHVM_METHOD(ZMQDevice, setTimerTimeout, int64_t milliseconds) {
  auto dev = Native::data<ZMQDevice>(this_);
  dev->timer_cb.timeout = milliseconds;
  return Object(Native::object(dev));
}

Object HHVM_METHOD(ZMQDevice, setIdleCallback, const Variant& idleCallback, int64_t timeout, const Variant& userData) {
  auto dev = Native::data<ZMQDevice>(this_);
  dev->idle_cb.clear();
  dev->idle_cb.assign(idleCallback, timeout, userData);
  return Object(Native::object(dev));
}

Object HHVM_METHOD(ZMQDevice, setTimerCallback, const Variant& timerCallback, int64_t timeout, const Variant& userData) {
  auto dev = Native::data<ZMQDevice>(this_);
  dev->timer_cb.clear();
  dev->timer_cb.assign(timerCallback, timeout, userData);
  return Object(Native::object(dev));
}

///////////////////////////////////////////////////////////////////////////////

static const StaticString
#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
  s_CTXOPT_MAX_SOCKETS("CTXOPT_MAX_SOCKETS"),
  s_CTXOPT_MAX_SOCKETS_DEFAULT("CTXOPT_MAX_SOCKETS_DEFAULT"),
#endif

  s_DEVICE_FORWARDER("DEVICE_FORWARDER"),
  s_DEVICE_QUEUE("DEVICE_QUEUE"),
  s_DEVICE_STREAMER("DEVICE_STREAMER"),

  s_ERR_INTERNAL("ERR_INTERNAL"),
  s_ERR_EAGAIN("ERR_EAGAIN"),
  s_ERR_ENOTSUP("ERR_ENOTSUP"),
  s_ERR_EFSM("ERR_EFSM"),
  s_ERR_ETERM("ERR_ETERM"),

  s_LIBZMQ_VER("LIBZMQ_VER"),

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0
  s_MODE_SNDLABEL("MODE_SNDLABEL"),
#endif
  s_MODE_SNDMORE("MODE_SNDMORE"),
  s_MODE_NOBLOCK("MODE_NOBLOCK"),
  s_MODE_DONTWAIT("MODE_DONTWAIT"),

  s_POLL_IN("POLL_IN"),
  s_POLL_OUT("POLL_OUT"),

  s_SOCKET_PAIR("SOCKET_PAIR"),
  s_SOCKET_PUB("SOCKET_PUB"),
  s_SOCKET_SUB("SOCKET_SUB"),
#if ZMQ_VERSION_MAJOR >= 3
  s_SOCKET_XSUB("SOCKET_XSUB"),
  s_SOCKET_XPUB("SOCKET_XPUB"),
#endif
  s_SOCKET_REQ("SOCKET_REQ"),
  s_SOCKET_REP("SOCKET_REP"),
  s_SOCKET_XREQ("SOCKET_XREQ"),
  s_SOCKET_XREP("SOCKET_XREP"),
  s_SOCKET_PUSH("SOCKET_PUSH"),
  s_SOCKET_PULL("SOCKET_PULL"),
  s_SOCKET_DEALER("SOCKET_DEALER"),
  s_SOCKET_ROUTER("SOCKET_ROUTER"),
#if ZMQ_VERSION_MAJOR >= 4
  s_SOCKET_STREAM("SOCKET_STREAM"),
#endif
  s_SOCKET_UPSTREAM("SOCKET_UPSTREAM"),
  s_SOCKET_DOWNSTREAM("SOCKET_DOWNSTREAM"),

  s_ZMQ("ZMQ"),
  s_ZMQPoll("ZMQPoll"),
  s_ZMQDevice("ZMQDevice");

void ZMQExtension::moduleInit() {
  HHVM_STATIC_ME(ZMQ, clock);

  Native::registerNativeDataInfo<ZMQContext>(s_ZMQContext.get());
  HHVM_ME(ZMQContext, __construct);
  HHVM_STATIC_ME(ZMQContext, acquire);
  HHVM_ME(ZMQContext, isPersistent);
#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
  HHVM_ME(ZMQContext, getOpt);
  HHVM_ME(ZMQContext, setOpt);
#endif
  HHVM_ME(ZMQContext, getSocket);

  Native::registerNativeDataInfo<ZMQSocket>(s_ZMQSocket.get());
  HHVM_ME(ZMQSocket, __construct);
  HHVM_ME(ZMQSocket, send);
  HHVM_MALIAS(ZMQSocket, sendMsg, ZMQSocket, send);
  HHVM_ME(ZMQSocket, sendMulti);
  HHVM_ME(ZMQSocket, recv);
  HHVM_MALIAS(ZMQSocket, recvMsg, ZMQSocket, recv);
  HHVM_ME(ZMQSocket, recvMulti);
  HHVM_ME(ZMQSocket, getPersistentId);
  HHVM_ME(ZMQSocket, bind);
  HHVM_ME(ZMQSocket, connect);
#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
  HHVM_ME(ZMQSocket, unbind);
  HHVM_ME(ZMQSocket, disconnect);
#endif
  HHVM_ME(ZMQSocket, getEndpoints);
  HHVM_ME(ZMQSocket, getSocketType);
  HHVM_ME(ZMQSocket, isPersistent);


  Native::registerNativeDataInfo<ZMQPoll>(s_ZMQPoll.get());
  HHVM_ME(ZMQPoll, add);
  HHVM_ME(ZMQPoll, remove);
  HHVM_ME(ZMQPoll, poll);
  HHVM_ME(ZMQPoll, count);
  HHVM_ME(ZMQPoll, clear);

  Native::registerNativeDataInfo<ZMQDevice>(s_ZMQDevice.get());
  HHVM_ME(ZMQDevice, __construct);
  HHVM_ME(ZMQDevice, run);
  HHVM_ME(ZMQDevice, getIdleTimeout);
  HHVM_ME(ZMQDevice, setIdleTimeout);
  HHVM_ME(ZMQDevice, getTimerTimeout);
  HHVM_ME(ZMQDevice, setTimerTimeout);
  HHVM_ME(ZMQDevice, setIdleCallback);
  HHVM_ME(ZMQDevice, setTimerCallback);

#define REGISTER_ZMQ_CONST(const_name, value) \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_##const_name.get(), value);

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
  REGISTER_ZMQ_CONST(CTXOPT_MAX_SOCKETS, ZMQ_MAX_SOCKETS);
  REGISTER_ZMQ_CONST(CTXOPT_MAX_SOCKETS_DEFAULT, ZMQ_MAX_SOCKETS_DFLT);
#endif

  REGISTER_ZMQ_CONST(DEVICE_FORWARDER, ZMQ_FORWARDER);
  REGISTER_ZMQ_CONST(DEVICE_QUEUE, ZMQ_QUEUE);
  REGISTER_ZMQ_CONST(DEVICE_STREAMER, ZMQ_STREAMER);

  REGISTER_ZMQ_CONST(ERR_INTERNAL, PHP_ZMQ_INTERNAL_ERROR);
  REGISTER_ZMQ_CONST(ERR_EAGAIN, EAGAIN);
  REGISTER_ZMQ_CONST(ERR_ENOTSUP, ENOTSUP);
  REGISTER_ZMQ_CONST(ERR_EFSM, EFSM);
  REGISTER_ZMQ_CONST(ERR_ETERM, ETERM);

  Native::registerClassConstant<KindOfString>(s_ZMQ.get(), s_LIBZMQ_VER.get(), ZMQ::getLibVersion().get());

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0
  REGISTER_ZMQ_CONST(MODE_SNDLABEL, ZMQ_SNDLABEL);
#endif
  REGISTER_ZMQ_CONST(MODE_SNDMORE, ZMQ_SNDMORE);
  REGISTER_ZMQ_CONST(MODE_NOBLOCK, ZMQ_DONTWAIT);
  REGISTER_ZMQ_CONST(MODE_DONTWAIT, ZMQ_DONTWAIT);

  REGISTER_ZMQ_CONST(POLL_IN, ZMQ_POLLIN);
  REGISTER_ZMQ_CONST(POLL_OUT, ZMQ_POLLOUT);

  /* Socket constants */
  REGISTER_ZMQ_CONST(SOCKET_PAIR, ZMQ_PAIR);
  REGISTER_ZMQ_CONST(SOCKET_PUB, ZMQ_PUB);
  REGISTER_ZMQ_CONST(SOCKET_SUB, ZMQ_SUB);
#if ZMQ_VERSION_MAJOR >= 3
  REGISTER_ZMQ_CONST(SOCKET_XSUB, ZMQ_XSUB);
  REGISTER_ZMQ_CONST(SOCKET_XPUB, ZMQ_XPUB);
#endif
  REGISTER_ZMQ_CONST(SOCKET_REQ, ZMQ_REQ);
  REGISTER_ZMQ_CONST(SOCKET_REP, ZMQ_REP);
  REGISTER_ZMQ_CONST(SOCKET_XREQ, ZMQ_XREQ);
  REGISTER_ZMQ_CONST(SOCKET_XREP, ZMQ_XREP);
  REGISTER_ZMQ_CONST(SOCKET_PUSH, ZMQ_PUSH);
  REGISTER_ZMQ_CONST(SOCKET_PULL, ZMQ_PULL);
  REGISTER_ZMQ_CONST(SOCKET_DEALER, ZMQ_DEALER);
  REGISTER_ZMQ_CONST(SOCKET_ROUTER, ZMQ_ROUTER);
#if ZMQ_VERSION_MAJOR >= 4
  REGISTER_ZMQ_CONST(SOCKET_STREAM, ZMQ_STREAM);
#endif

  REGISTER_ZMQ_CONST(SOCKET_UPSTREAM, ZMQ_PULL);
  REGISTER_ZMQ_CONST(SOCKET_DOWNSTREAM, ZMQ_PUSH);
#undef REGISTER_ZMQ_CONST

  registerSockoptConstants();

  loadSystemlib();

  ZMQ::initializeClock();
  initializeExceptionReferences();
}

void ZMQExtension::moduleInfo(Array &info) {
  Extension::moduleInfo(info);
  info.set(String("ZMQ extension"), "enabled");
  info.set(String("ZMQ extension version"), PHP_ZMQ_VERSION);
  info.set(String("libzmq version"), ZMQ::getLibVersion());
}

}}
