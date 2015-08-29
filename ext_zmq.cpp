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

Class* s_ZMQContextClass;
Class* s_ZMQExceptionClass;
Class* s_ZMQContextExceptionClass;
Class* s_ZMQSocketExceptionClass;
Class* s_ZMQPollExceptionClass;
Class* s_ZMQDeviceExceptionClass;

static const StaticString
  s_ZMQContext("ZMQContext"),
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

static ZMQContextData* php_zmq_context_new(int io_threads, bool is_persistent, bool is_global) {
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
void HHVM_METHOD(ZMQContext, __construct, int io_threads, bool is_persistent) {
  auto cont = Native::data<ZMQContext>(this_);

  char listKey[48];
  if (is_persistent) {
    snprintf(listKey, 48, "zmq_context:[%d]", io_threads);
    cont->context = s_persistent_context_list.find(listKey)->second;
    return;
  }

  cont->context = php_zmq_context_new(io_threads, is_persistent, false);
  if (!cont->context) {
    throwExceptionClass(s_ZMQContextExceptionClass, folly::format("Error creating context: {}", zmq_strerror(errno)).str(), errno);
  }

  if (is_persistent) {
    s_persistent_context_list[listKey] = cont->context;
  }
}

Object HHVM_METHOD(ZMQContext, acquire) {
  auto obj = createObject(s_ZMQContextClass);
  auto intern = Native::data<ZMQContext>(obj);
  intern->context = php_zmq_context_new(1, true, true);
  return obj;
}

bool HHVM_METHOD(ZMQContext, isPersistent) {
  return Native::data<ZMQContext>(this_)->context->is_persistent;
}

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
int HHVM_METHOD(ZMQContext, getOpt, int option) {
  auto ctx = Native::data<ZMQContext>(this_);
  
  if (option != ZMQ_MAX_SOCKETS) {
    throwExceptionClass(s_ZMQContextExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }

  int value = zmq_ctx_get(ctx->context->z_ctx, option);
  return value;
}

void HHVM_METHOD(ZMQContext, setOpt, int option, int value) {
  auto ctx = Native::data<ZMQContext>(this_);

  if (option != ZMQ_MAX_SOCKETS) {
    throwExceptionClass(s_ZMQContextExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }

  if (zmq_ctx_set(ctx->context->z_ctx, option, value) != 0) {
    throwExceptionClass(s_ZMQContextExceptionClass, folly::format("Failed to set the option ZMQ::CTXOPT_MAX_SOCKETS value: {}", zmq_strerror(errno)).str(), errno);
  }
}
#endif

void ZMQExtension::registerClasses() {
  HHVM_ME(ZMQContext, __construct);
  HHVM_ME(ZMQContext, acquire);
  HHVM_ME(ZMQContext, isPersistent);

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
  HHVM_ME(ZMQContext, getOpt);
  HHVM_ME(ZMQContext, setOpt);
#endif
}

}}
