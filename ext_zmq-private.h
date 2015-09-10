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

#include <zmq.h>

#include <stdint.h>

/* Compatibility macros between zeromq 2.x and 3.x */
#ifndef ZMQ_DONTWAIT
#	define ZMQ_DONTWAIT ZMQ_NOBLOCK
#endif
#ifndef ZMQ_HWM
# define ZMQ_HWM (ZMQ_DONTWAIT + 200)
#endif
#ifndef ZMQ_FORWARDER
# define ZMQ_FORWARDER 0
#endif
#ifndef ZMQ_QUEUE
# define ZMQ_QUEUE 0
#endif
#ifndef ZMQ_STREAMER
# define ZMQ_STREAMER 0
#endif
#if ZMQ_VERSION_MAJOR == 2
#	define zmq_sendmsg zmq_send
#	define zmq_recvmsg zmq_recv
#	define PHP_ZMQ_TIMEOUT 1000
#else
#	define PHP_ZMQ_TIMEOUT 1
#endif

#define PHP_ZMQ_INTERNAL_ERROR -99

#endif /* _PHP_ZMQ_PRIVATE_H_ */
