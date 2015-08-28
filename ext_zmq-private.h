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

#ifndef incl_HPHP_EXT_ZMQ_PRIVATE_H_
#define incl_HPHP_EXT_ZMQ_PRIVATE_H_

#include "zmq.h"

#ifdef HAVE_CZMQ
# include <czmq.h>
# if CZMQ_VERSION_MAJOR >= 2
#  define HAVE_CZMQ_2
# endif
#endif

#include <stdint.h>

#ifdef ZTS
# define ZMQ_G(v) TSRMG(php_zmq_globals_id, zend_php_zmq_globals *, v)
#else
# define ZMQ_G(v) (php_zmq_globals.v)
#endif

#define PHP_ZMQ_CONTEXT_OBJECT (php_zmq_context_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

#define PHP_ZMQ_SOCKET_OBJECT (php_zmq_socket_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

#define PHP_ZMQ_POLL_OBJECT (php_zmq_poll_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

#define PHP_ZMQ_DEVICE_OBJECT (php_zmq_device_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

#define ZMQ_RETURN_THIS RETURN_ZVAL(getThis(), 1, 0);

#ifndef Z_ADDREF_P
# define Z_ADDREF_P(pz) (pz)->refcount++
#endif

#ifndef Z_DELREF_P
# define Z_DELREF_P(pz) (pz)->refcount--
#endif

#ifndef Z_REFCOUNT_P
# define Z_REFCOUNT_P(pz) (pz)->refcount
#endif

#if ZEND_MODULE_API_NO > 20060613

#define PHP_ZMQ_ERROR_HANDLING_INIT() zend_error_handling error_handling;

#define PHP_ZMQ_ERROR_HANDLING_THROW() zend_replace_error_handling(EH_THROW, php_zmq_socket_exception_sc_entry, &error_handling TSRMLS_CC);

#define PHP_ZMQ_ERROR_HANDLING_RESTORE() zend_restore_error_handling(&error_handling TSRMLS_CC);

#else

#define PHP_ZMQ_ERROR_HANDLING_INIT()

#define PHP_ZMQ_ERROR_HANDLING_THROW() php_set_error_handling(EH_THROW, php_zmq_socket_exception_sc_entry TSRMLS_CC);

#define PHP_ZMQ_ERROR_HANDLING_RESTORE() php_set_error_handling(EH_NORMAL, NULL TSRMLS_CC);

#endif

/* Compatibility macros between zeromq 2.x and 3.x */
#ifndef ZMQ_DONTWAIT
#	define ZMQ_DONTWAIT ZMQ_NOBLOCK
#endif
#ifndef ZMQ_HWM
#   define ZMQ_HWM (ZMQ_DONTWAIT + 200)
#endif
#ifndef ZMQ_FORWARDER
#   define ZMQ_FORWARDER 0
#endif
#ifndef ZMQ_QUEUE
#   define ZMQ_QUEUE 0
#endif
#ifndef ZMQ_STREAMER
#   define ZMQ_STREAMER 0
#endif
#if ZMQ_VERSION_MAJOR == 2
#	define zmq_sendmsg zmq_send
#	define zmq_recvmsg zmq_recv
#	define PHP_ZMQ_TIMEOUT 1000
#else
#	define PHP_ZMQ_TIMEOUT 1
#endif

#define PHP_ZMQ_INTERNAL_ERROR -99

#define PHP_ZMQ_VERSION_LEN 24

#ifdef HAVE_CZMQ_2
# define PHP_ZMQ_AUTH_TYPE_PLAIN 0
# define PHP_ZMQ_AUTH_TYPE_CURVE 1
#endif

namespace HPHP { namespace zmq {

extern Class* s_ZMQExceptionClass;
extern Class* s_ZMQContextExceptionClass;
extern Class* s_ZMQSocketExceptionClass;
extern Class* s_ZMQPollExceptionClass;
extern Class* s_ZMQDeviceExceptionClass;

[[noreturn]] void throwExceptionClass(Class* cls, const Variant& msg, const Variant& code);

}}

#endif /* _PHP_ZMQ_PRIVATE_H_ */
