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

#include "hphp/runtime/base/array-init.h"
#include "hphp/runtime/vm/native-data.h"

namespace HPHP {

namespace zmq {

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

Class* s_ZMQExceptionClass;
Class* s_ZMQContextExceptionClass;
Class* s_ZMQSocketExceptionClass;
Class* s_ZMQPollExceptionClass;
Class* s_ZMQDeviceExceptionClass;

static const StaticString
  s_ZMQException("ZMQException"),
  s_ZMQContextException("ZMQContextException"),
  s_ZMQSocketException("ZMQSocketException"),
  s_ZMQPollException("ZMQPollException"),
  s_ZMQDeviceException("ZMQDeviceException");

void ZMQExtension::initializeExceptionReferences() {
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

void HHVM_METHOD(ZMQContext, __construct, int io_threads, bool is_persistent) {

}

bool HHVM_METHOD(ZMQContext, isPersistent) {
  return Native::data<ZMQContextObject>(this_)->context->is_persistent;
}

void ZMQExtension::registerClasses() {
  HHVM_ME(ZMQContext, __construct);
  HHVM_ME(ZMQContext, isPersistent);
}

}}
