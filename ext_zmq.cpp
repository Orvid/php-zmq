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

#include "hphp/runtime/base/array-init.h"
#include "hphp/runtime/vm/native-data.h"

#include "tbb/concurrent_unordered_map.h"

namespace HPHP {

namespace zmq {

static Object createObject(Class* cls) {
  return Object::attach(g_context->createObject(cls, Variant(Variant::NullInit()), false));
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
Class* s_ZMQExceptionClass;
Class* s_ZMQContextExceptionClass;
Class* s_ZMQSocketExceptionClass;
Class* s_ZMQPollExceptionClass;
Class* s_ZMQDeviceExceptionClass;

static const StaticString
  s_ZMQContext("ZMQContext"),
  s_ZMQSocket("ZMQSocket"),
  s_ZMQException("ZMQException"),
  s_ZMQContextException("ZMQContextException"),
  s_ZMQSocketException("ZMQSocketException"),
  s_ZMQPollException("ZMQPollException"),
  s_ZMQDeviceException("ZMQDeviceException");

void ZMQExtension::initializeExceptionReferences() {
  s_ZMQContextClass = NamedEntity::get(s_ZMQContext.get())->clsList();
  s_ZMQExceptionClass = NamedEntity::get(s_ZMQException.get())->clsList();
  s_ZMQContextExceptionClass = NamedEntity::get(s_ZMQContextException.get())->clsList();
  s_ZMQSocketExceptionClass = NamedEntity::get(s_ZMQSocketException.get())->clsList();
  s_ZMQPollExceptionClass = NamedEntity::get(s_ZMQPollException.get())->clsList();
  s_ZMQDeviceExceptionClass = NamedEntity::get(s_ZMQDeviceException.get())->clsList();
}

///////////////////////////////////////////////////////////////////////////////

static ZMQExtension s_zmq_extension;

// Uncomment for non-bundled module
//HHVM_GET_MODULE(zmq);

///////////////////////////////////////////////////////////////////////////////
// ZMQContext
///////////////////////////////////////////////////////////////////////////////

ZMQContextData* ZMQContext::createData(int64_t io_threads, bool is_persistent, bool is_global) {
  auto ctx = new ZMQContextData(io_threads, is_persistent, is_global);

  if (is_global) {
    static std::once_flag flag;
    static void* globalContext;
    std::call_once(flag, [&] {
      globalContext = zmq_init(io_threads);
    });
    ctx->z_ctx = globalContext;
  } else {
    ctx->z_ctx = zmq_init(io_threads);
  }

  if (!ctx->z_ctx) {
    delete ctx;
    return nullptr;
  }

  return ctx;
}

static tbb::concurrent_unordered_map<char*, ZMQContextData*> s_persistent_context_list;
void HHVM_METHOD(ZMQContext, __construct, int64_t io_threads, bool is_persistent) {
  auto cont = Native::data<ZMQContext>(this_);

  char listKey[48];
  if (is_persistent) {
    snprintf(listKey, 48, "zmq_context:[%d]", io_threads);
    auto ct = s_persistent_context_list.find(listKey);
    if (ct != s_persistent_context_list.end()) {
      cont->context = ct->second;
      return;
    }
  }

  cont->context = ZMQContext::createData(io_threads, is_persistent, false);
  if (!cont->context) {
    throwExceptionClassZMQErr(s_ZMQContextExceptionClass, "Error creating context: {}", errno);
  }

  if (is_persistent) {
    s_persistent_context_list[listKey] = cont->context;
  }
}

Object HHVM_STATIC_METHOD(ZMQContext, acquire) {
  auto obj = createObject(s_ZMQContextClass);
  auto intern = Native::data<ZMQContext>(obj);
  intern->context = ZMQContext::createData(1, true, true);
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

///////////////////////////////////////////////////////////////////////////////
// ZMQSocket
///////////////////////////////////////////////////////////////////////////////


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

  if (sock->socket->is_persistent && sock->persistent_id) {
    return String(sock->persistent_id, CopyString);
  }
  return nullptr;
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

void ZMQExtension::moduleInit() {
  loadSystemlib();
  registerSockoptConstants();

  // TODO: ZMQContext NDI

  initializeExceptionReferences();

  HHVM_ME(ZMQContext, __construct);
  HHVM_STATIC_ME(ZMQContext, acquire);
  HHVM_ME(ZMQContext, isPersistent);

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
  HHVM_ME(ZMQContext, getOpt);
  HHVM_ME(ZMQContext, setOpt);
#endif

  Native::registerNativeDataInfo<ZMQSocket>(s_ZMQSocket.get(),
                                            Native::NDIFlags::NO_SWEEP);
  HHVM_ME(ZMQSocket, send);
  HHVM_ME(ZMQSocket, sendMulti);
  HHVM_ME(ZMQSocket, recv);
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
}

}}
