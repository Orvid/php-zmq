
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

#include "hphp/runtime/base/type-string.h"
#include "hphp/runtime/vm/native-data.h"
#include "ext_zmq.h"
#include "ext_zmq-private.h"

namespace HPHP { namespace zmq {
extern Class* s_ZMQSocketExceptionClass;
[[noreturn]]
extern void throwExceptionClassZMQErr(Class* cls, std::string msg, int err);
[[noreturn]]
extern void throwExceptionClass(Class* cls, const Variant& msg, const Variant& code);

[[noreturn]]
static void throwSocketExceptionZMQErr(std::string msg, int err) {
  throwExceptionClassZMQErr(s_ZMQSocketExceptionClass, msg, err);
}

[[noreturn]]
static void throwSocketException(std::string msg, int err) {
  throwExceptionClass(s_ZMQSocketExceptionClass, msg, err);
}
  
#if ZMQ_VERSION_MAJOR == 2 && ZMQ_VERSION_MINOR < 2

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocket>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  	
    case ZMQ_HWM:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_HWM value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SWAP:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SWAP value: {}", errno);
      }
      return value;
    }	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", errno);
      }
      return value;
    }
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }	
    case ZMQ_RATE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECOVERY_IVL:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECOVERY_IVL_MSEC:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL_MSEC value: {}", errno);
      }
      return value;
    }	
    case ZMQ_MCAST_LOOP:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_MCAST_LOOP value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDBUF:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVBUF:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", errno);
      }
      return value;
    }	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", errno);
      }
      return value;
    }
    case ZMQ_SUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVMORE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_EVENTS:
    {
      uint32_t value;
      value_len = sizeof(uint32_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", errno);
      }
      return value;
    }
    case ZMQ_FD:
    {
      return Resource(req::make<ZMQFd>(Object(this_)));
    }
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

/*
  Set a socket option
*/
Object HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocket>(this_);
  int status;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  
    case ZMQ_HWM:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_HWM value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", errno);
      }
      break;
    }
    case ZMQ_SWAP:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SWAP option: {}", errno);
      }
      break;
    }
    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", errno);
      }
      break;
    }
    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", errno);
      }
      break;
    }
    case ZMQ_RATE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", errno);
      }
      break;
    }
    case ZMQ_RECOVERY_IVL:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_RECOVERY_IVL_MSEC:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL_MSEC option: {}", errno);
      }
      break;
    }
    case ZMQ_MCAST_LOOP:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_MCAST_LOOP option: {}", errno);
      }
      break;
    }
    case ZMQ_SNDBUF:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_SNDBUF value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVBUF:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_RCVBUF value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", errno);
      }
      break;
    }
    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", errno);
      }
      break;
    }
    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_TYPE:
      throwSocketException("Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwSocketException("Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return Object(Native::object(intern));
}

static const StaticString
  s_ZMQ("ZMQ"),
  s_SOCKOPT_HWM("SOCKOPT_HWM"),
  s_SOCKOPT_SWAP("SOCKOPT_SWAP"),
  s_SOCKOPT_AFFINITY("SOCKOPT_AFFINITY"),
  s_SOCKOPT_IDENTITY("SOCKOPT_IDENTITY"),
  s_SOCKOPT_RATE("SOCKOPT_RATE"),
  s_SOCKOPT_RECOVERY_IVL("SOCKOPT_RECOVERY_IVL"),
  s_SOCKOPT_RECOVERY_IVL_MSEC("SOCKOPT_RECOVERY_IVL_MSEC"),
  s_SOCKOPT_MCAST_LOOP("SOCKOPT_MCAST_LOOP"),
  s_SOCKOPT_SNDBUF("SOCKOPT_SNDBUF"),
  s_SOCKOPT_RCVBUF("SOCKOPT_RCVBUF"),
  s_SOCKOPT_LINGER("SOCKOPT_LINGER"),
  s_SOCKOPT_RECONNECT_IVL("SOCKOPT_RECONNECT_IVL"),
  s_SOCKOPT_RECONNECT_IVL_MAX("SOCKOPT_RECONNECT_IVL_MAX"),
  s_SOCKOPT_BACKLOG("SOCKOPT_BACKLOG"),
  s_SOCKOPT_SUBSCRIBE("SOCKOPT_SUBSCRIBE"),
  s_SOCKOPT_UNSUBSCRIBE("SOCKOPT_UNSUBSCRIBE"),
  s_SOCKOPT_TYPE("SOCKOPT_TYPE"),
  s_SOCKOPT_RCVMORE("SOCKOPT_RCVMORE"),
  s_SOCKOPT_FD("SOCKOPT_FD"),
  s_SOCKOPT_EVENTS("SOCKOPT_EVENTS");

void ZMQExtension::registerSockoptConstants()
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_SOCKOPT_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(HWM, ZMQ_HWM);
  PHP_ZMQ_REGISTER_SOCKOPT(SWAP, ZMQ_SWAP);
  PHP_ZMQ_REGISTER_SOCKOPT(AFFINITY, ZMQ_AFFINITY);
  PHP_ZMQ_REGISTER_SOCKOPT(IDENTITY, ZMQ_IDENTITY);
  PHP_ZMQ_REGISTER_SOCKOPT(RATE, ZMQ_RATE);
  PHP_ZMQ_REGISTER_SOCKOPT(RECOVERY_IVL, ZMQ_RECOVERY_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(RECOVERY_IVL_MSEC, ZMQ_RECOVERY_IVL_MSEC);
  PHP_ZMQ_REGISTER_SOCKOPT(MCAST_LOOP, ZMQ_MCAST_LOOP);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDBUF, ZMQ_SNDBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVBUF, ZMQ_RCVBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(LINGER, ZMQ_LINGER);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL, ZMQ_RECONNECT_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
  PHP_ZMQ_REGISTER_SOCKOPT(BACKLOG, ZMQ_BACKLOG);
  PHP_ZMQ_REGISTER_SOCKOPT(SUBSCRIBE, ZMQ_SUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(TYPE, ZMQ_TYPE);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVMORE, ZMQ_RCVMORE);
  PHP_ZMQ_REGISTER_SOCKOPT(FD, ZMQ_FD);
  PHP_ZMQ_REGISTER_SOCKOPT(EVENTS, ZMQ_EVENTS);
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

#if ZMQ_VERSION_MAJOR == 2 && ZMQ_VERSION_MINOR >= 2

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocket>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  	
    case ZMQ_HWM:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_HWM value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SWAP:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SWAP value: {}", errno);
      }
      return value;
    }	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", errno);
      }
      return value;
    }
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }	
    case ZMQ_RATE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECOVERY_IVL:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECOVERY_IVL_MSEC:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL_MSEC value: {}", errno);
      }
      return value;
    }	
    case ZMQ_MCAST_LOOP:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_MCAST_LOOP value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDBUF:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVBUF:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", errno);
      }
      return value;
    }	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", errno);
      }
      return value;
    }
    case ZMQ_SUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVMORE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_EVENTS:
    {
      uint32_t value;
      value_len = sizeof(uint32_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: {}", errno);
      }
      return value;
    }
    case ZMQ_FD:
    {
      return Resource(req::make<ZMQFd>(Object(this_)));
    }
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

/*
  Set a socket option
*/
Object HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocket>(this_);
  int status;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  
    case ZMQ_HWM:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_HWM value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", errno);
      }
      break;
    }
    case ZMQ_SWAP:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SWAP option: {}", errno);
      }
      break;
    }
    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", errno);
      }
      break;
    }
    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", errno);
      }
      break;
    }
    case ZMQ_RATE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", errno);
      }
      break;
    }
    case ZMQ_RECOVERY_IVL:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_RECOVERY_IVL_MSEC:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL_MSEC option: {}", errno);
      }
      break;
    }
    case ZMQ_MCAST_LOOP:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_MCAST_LOOP option: {}", errno);
      }
      break;
    }
    case ZMQ_SNDBUF:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_SNDBUF value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVBUF:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_RCVBUF value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", errno);
      }
      break;
    }
    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", errno);
      }
      break;
    }
    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_TYPE:
      throwSocketException("Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwSocketException("Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_SNDTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: {}", errno);
      }
      break;
    }
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return Object(Native::object(intern));
}

static const StaticString
  s_ZMQ("ZMQ"),
  s_SOCKOPT_HWM("SOCKOPT_HWM"),
  s_SOCKOPT_SWAP("SOCKOPT_SWAP"),
  s_SOCKOPT_AFFINITY("SOCKOPT_AFFINITY"),
  s_SOCKOPT_IDENTITY("SOCKOPT_IDENTITY"),
  s_SOCKOPT_RATE("SOCKOPT_RATE"),
  s_SOCKOPT_RECOVERY_IVL("SOCKOPT_RECOVERY_IVL"),
  s_SOCKOPT_RECOVERY_IVL_MSEC("SOCKOPT_RECOVERY_IVL_MSEC"),
  s_SOCKOPT_MCAST_LOOP("SOCKOPT_MCAST_LOOP"),
  s_SOCKOPT_SNDBUF("SOCKOPT_SNDBUF"),
  s_SOCKOPT_RCVBUF("SOCKOPT_RCVBUF"),
  s_SOCKOPT_LINGER("SOCKOPT_LINGER"),
  s_SOCKOPT_RECONNECT_IVL("SOCKOPT_RECONNECT_IVL"),
  s_SOCKOPT_RECONNECT_IVL_MAX("SOCKOPT_RECONNECT_IVL_MAX"),
  s_SOCKOPT_BACKLOG("SOCKOPT_BACKLOG"),
  s_SOCKOPT_SUBSCRIBE("SOCKOPT_SUBSCRIBE"),
  s_SOCKOPT_UNSUBSCRIBE("SOCKOPT_UNSUBSCRIBE"),
  s_SOCKOPT_TYPE("SOCKOPT_TYPE"),
  s_SOCKOPT_RCVMORE("SOCKOPT_RCVMORE"),
  s_SOCKOPT_FD("SOCKOPT_FD"),
  s_SOCKOPT_EVENTS("SOCKOPT_EVENTS"),
  s_SOCKOPT_SNDTIMEO("SOCKOPT_SNDTIMEO"),
  s_SOCKOPT_RCVTIMEO("SOCKOPT_RCVTIMEO");

void ZMQExtension::registerSockoptConstants()
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_SOCKOPT_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(HWM, ZMQ_HWM);
  PHP_ZMQ_REGISTER_SOCKOPT(SWAP, ZMQ_SWAP);
  PHP_ZMQ_REGISTER_SOCKOPT(AFFINITY, ZMQ_AFFINITY);
  PHP_ZMQ_REGISTER_SOCKOPT(IDENTITY, ZMQ_IDENTITY);
  PHP_ZMQ_REGISTER_SOCKOPT(RATE, ZMQ_RATE);
  PHP_ZMQ_REGISTER_SOCKOPT(RECOVERY_IVL, ZMQ_RECOVERY_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(RECOVERY_IVL_MSEC, ZMQ_RECOVERY_IVL_MSEC);
  PHP_ZMQ_REGISTER_SOCKOPT(MCAST_LOOP, ZMQ_MCAST_LOOP);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDBUF, ZMQ_SNDBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVBUF, ZMQ_RCVBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(LINGER, ZMQ_LINGER);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL, ZMQ_RECONNECT_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
  PHP_ZMQ_REGISTER_SOCKOPT(BACKLOG, ZMQ_BACKLOG);
  PHP_ZMQ_REGISTER_SOCKOPT(SUBSCRIBE, ZMQ_SUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(TYPE, ZMQ_TYPE);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVMORE, ZMQ_RCVMORE);
  PHP_ZMQ_REGISTER_SOCKOPT(FD, ZMQ_FD);
  PHP_ZMQ_REGISTER_SOCKOPT(EVENTS, ZMQ_EVENTS);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDTIMEO, ZMQ_SNDTIMEO);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVTIMEO, ZMQ_RCVTIMEO);
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocket>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  	
    case ZMQ_SNDHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDHWM value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVHWM value: {}", errno);
      }
      return value;
    }	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", errno);
      }
      return value;
    }
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }	
    case ZMQ_RATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECOVERY_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", errno);
      }
      return value;
    }	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", errno);
      }
      return value;
    }	
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: {}", errno);
      }
      return value;
    }
    case ZMQ_SUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVMORE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_EVENTS:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVLABEL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVLABEL value: {}", errno);
      }
      return value;
    }
    case ZMQ_FD:
    {
      return Resource(req::make<ZMQFd>(Object(this_)));
    }
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

/*
  Set a socket option
*/
Object HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocket>(this_);
  int status;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  
    case ZMQ_SNDHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDHWM option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVHWM option: {}", errno);
      }
      break;
    }
    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", errno);
      }
      break;
    }
    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", errno);
      }
      break;
    }
    case ZMQ_RATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", errno);
      }
      break;
    }
    case ZMQ_RECOVERY_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_SNDBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", errno);
      }
      break;
    }
    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", errno);
      }
      break;
    }
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: {}", errno);
      }
      break;
    }
    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_TYPE:
      throwSocketException("Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwSocketException("Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_SNDTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVLABEL:
      throwSocketException("Setting ZMQ::SOCKOPT_RCVLABEL is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_HWM:
    {
      int64_t iVal = pz_value.toInt64();
      int value = (int)iVal;

      if (iVal < 0) {
        throwSocketException("The option must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
      
      status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

      if (status == 0) {
        status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
      }
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", errno);
      }
      break;
    }
  
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return Object(Native::object(intern));
}

static const StaticString
  s_ZMQ("ZMQ"),
  s_SOCKOPT_HWM("SOCKOPT_HWM"),
  s_SOCKOPT_SNDHWM("SOCKOPT_SNDHWM"),
  s_SOCKOPT_RCVHWM("SOCKOPT_RCVHWM"),
  s_SOCKOPT_AFFINITY("SOCKOPT_AFFINITY"),
  s_SOCKOPT_IDENTITY("SOCKOPT_IDENTITY"),
  s_SOCKOPT_RATE("SOCKOPT_RATE"),
  s_SOCKOPT_RECOVERY_IVL("SOCKOPT_RECOVERY_IVL"),
  s_SOCKOPT_SNDBUF("SOCKOPT_SNDBUF"),
  s_SOCKOPT_RCVBUF("SOCKOPT_RCVBUF"),
  s_SOCKOPT_LINGER("SOCKOPT_LINGER"),
  s_SOCKOPT_RECONNECT_IVL("SOCKOPT_RECONNECT_IVL"),
  s_SOCKOPT_RECONNECT_IVL_MAX("SOCKOPT_RECONNECT_IVL_MAX"),
  s_SOCKOPT_BACKLOG("SOCKOPT_BACKLOG"),
  s_SOCKOPT_MAXMSGSIZE("SOCKOPT_MAXMSGSIZE"),
  s_SOCKOPT_SUBSCRIBE("SOCKOPT_SUBSCRIBE"),
  s_SOCKOPT_UNSUBSCRIBE("SOCKOPT_UNSUBSCRIBE"),
  s_SOCKOPT_TYPE("SOCKOPT_TYPE"),
  s_SOCKOPT_RCVMORE("SOCKOPT_RCVMORE"),
  s_SOCKOPT_FD("SOCKOPT_FD"),
  s_SOCKOPT_EVENTS("SOCKOPT_EVENTS"),
  s_SOCKOPT_SNDTIMEO("SOCKOPT_SNDTIMEO"),
  s_SOCKOPT_RCVTIMEO("SOCKOPT_RCVTIMEO"),
  s_SOCKOPT_RCVLABEL("SOCKOPT_RCVLABEL");

void ZMQExtension::registerSockoptConstants()
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_SOCKOPT_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(HWM, ZMQ_HWM);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDHWM, ZMQ_SNDHWM);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVHWM, ZMQ_RCVHWM);
  PHP_ZMQ_REGISTER_SOCKOPT(AFFINITY, ZMQ_AFFINITY);
  PHP_ZMQ_REGISTER_SOCKOPT(IDENTITY, ZMQ_IDENTITY);
  PHP_ZMQ_REGISTER_SOCKOPT(RATE, ZMQ_RATE);
  PHP_ZMQ_REGISTER_SOCKOPT(RECOVERY_IVL, ZMQ_RECOVERY_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDBUF, ZMQ_SNDBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVBUF, ZMQ_RCVBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(LINGER, ZMQ_LINGER);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL, ZMQ_RECONNECT_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
  PHP_ZMQ_REGISTER_SOCKOPT(BACKLOG, ZMQ_BACKLOG);
  PHP_ZMQ_REGISTER_SOCKOPT(MAXMSGSIZE, ZMQ_MAXMSGSIZE);
  PHP_ZMQ_REGISTER_SOCKOPT(SUBSCRIBE, ZMQ_SUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(TYPE, ZMQ_TYPE);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVMORE, ZMQ_RCVMORE);
  PHP_ZMQ_REGISTER_SOCKOPT(FD, ZMQ_FD);
  PHP_ZMQ_REGISTER_SOCKOPT(EVENTS, ZMQ_EVENTS);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDTIMEO, ZMQ_SNDTIMEO);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVTIMEO, ZMQ_RCVTIMEO);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVLABEL, ZMQ_RCVLABEL);
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 1

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocket>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  	
    case ZMQ_SNDHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDHWM value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVHWM value: {}", errno);
      }
      return value;
    }	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", errno);
      }
      return value;
    }
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }	
    case ZMQ_RATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECOVERY_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", errno);
      }
      return value;
    }	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", errno);
      }
      return value;
    }	
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: {}", errno);
      }
      return value;
    }
    case ZMQ_SUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVMORE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_EVENTS:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: {}", errno);
      }
      return value;
    }
    case ZMQ_FD:
    {
      return Resource(req::make<ZMQFd>(Object(this_)));
    }
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

/*
  Set a socket option
*/
Object HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocket>(this_);
  int status;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  
    case ZMQ_SNDHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDHWM option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVHWM option: {}", errno);
      }
      break;
    }
    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", errno);
      }
      break;
    }
    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", errno);
      }
      break;
    }
    case ZMQ_RATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", errno);
      }
      break;
    }
    case ZMQ_RECOVERY_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_SNDBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", errno);
      }
      break;
    }
    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", errno);
      }
      break;
    }
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: {}", errno);
      }
      break;
    }
    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_TYPE:
      throwSocketException("Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwSocketException("Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_SNDTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: {}", errno);
      }
      break;
    }
    case ZMQ_HWM:
    {
      int64_t iVal = pz_value.toInt64();
      int value = (int)iVal;

      if (iVal < 0) {
        throwSocketException("The option must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
      
      status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

      if (status == 0) {
        status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
      }
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", errno);
      }
      break;
    }
  
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return Object(Native::object(intern));
}

static const StaticString
  s_ZMQ("ZMQ"),
  s_SOCKOPT_HWM("SOCKOPT_HWM"),
  s_SOCKOPT_SNDHWM("SOCKOPT_SNDHWM"),
  s_SOCKOPT_RCVHWM("SOCKOPT_RCVHWM"),
  s_SOCKOPT_AFFINITY("SOCKOPT_AFFINITY"),
  s_SOCKOPT_IDENTITY("SOCKOPT_IDENTITY"),
  s_SOCKOPT_RATE("SOCKOPT_RATE"),
  s_SOCKOPT_RECOVERY_IVL("SOCKOPT_RECOVERY_IVL"),
  s_SOCKOPT_SNDBUF("SOCKOPT_SNDBUF"),
  s_SOCKOPT_RCVBUF("SOCKOPT_RCVBUF"),
  s_SOCKOPT_LINGER("SOCKOPT_LINGER"),
  s_SOCKOPT_RECONNECT_IVL("SOCKOPT_RECONNECT_IVL"),
  s_SOCKOPT_RECONNECT_IVL_MAX("SOCKOPT_RECONNECT_IVL_MAX"),
  s_SOCKOPT_BACKLOG("SOCKOPT_BACKLOG"),
  s_SOCKOPT_MAXMSGSIZE("SOCKOPT_MAXMSGSIZE"),
  s_SOCKOPT_SUBSCRIBE("SOCKOPT_SUBSCRIBE"),
  s_SOCKOPT_UNSUBSCRIBE("SOCKOPT_UNSUBSCRIBE"),
  s_SOCKOPT_TYPE("SOCKOPT_TYPE"),
  s_SOCKOPT_RCVMORE("SOCKOPT_RCVMORE"),
  s_SOCKOPT_FD("SOCKOPT_FD"),
  s_SOCKOPT_EVENTS("SOCKOPT_EVENTS"),
  s_SOCKOPT_SNDTIMEO("SOCKOPT_SNDTIMEO"),
  s_SOCKOPT_RCVTIMEO("SOCKOPT_RCVTIMEO");

void ZMQExtension::registerSockoptConstants()
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_SOCKOPT_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(HWM, ZMQ_HWM);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDHWM, ZMQ_SNDHWM);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVHWM, ZMQ_RCVHWM);
  PHP_ZMQ_REGISTER_SOCKOPT(AFFINITY, ZMQ_AFFINITY);
  PHP_ZMQ_REGISTER_SOCKOPT(IDENTITY, ZMQ_IDENTITY);
  PHP_ZMQ_REGISTER_SOCKOPT(RATE, ZMQ_RATE);
  PHP_ZMQ_REGISTER_SOCKOPT(RECOVERY_IVL, ZMQ_RECOVERY_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDBUF, ZMQ_SNDBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVBUF, ZMQ_RCVBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(LINGER, ZMQ_LINGER);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL, ZMQ_RECONNECT_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
  PHP_ZMQ_REGISTER_SOCKOPT(BACKLOG, ZMQ_BACKLOG);
  PHP_ZMQ_REGISTER_SOCKOPT(MAXMSGSIZE, ZMQ_MAXMSGSIZE);
  PHP_ZMQ_REGISTER_SOCKOPT(SUBSCRIBE, ZMQ_SUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(TYPE, ZMQ_TYPE);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVMORE, ZMQ_RCVMORE);
  PHP_ZMQ_REGISTER_SOCKOPT(FD, ZMQ_FD);
  PHP_ZMQ_REGISTER_SOCKOPT(EVENTS, ZMQ_EVENTS);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDTIMEO, ZMQ_SNDTIMEO);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVTIMEO, ZMQ_RCVTIMEO);
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 2 && ZMQ_VERSION_PATCH == 0)

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocket>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  	
    case ZMQ_SNDHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDHWM value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVHWM value: {}", errno);
      }
      return value;
    }	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", errno);
      }
      return value;
    }
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }	
    case ZMQ_RATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECOVERY_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", errno);
      }
      return value;
    }	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", errno);
      }
      return value;
    }	
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: {}", errno);
      }
      return value;
    }
    case ZMQ_SUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVMORE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_EVENTS:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: {}", errno);
      }
      return value;
    }	
    case ZMQ_IPV4ONLY:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_IPV4ONLY value: {}", errno);
      }
      return value;
    }
    case ZMQ_LAST_ENDPOINT:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_LAST_ENDPOINT value: {}", errno);
      }
      return String(value, value_len - 1, CopyString);
    }	
    case ZMQ_TCP_KEEPALIVE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_TCP_KEEPALIVE_IDLE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_TCP_KEEPALIVE_CNT:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT value: {}", errno);
      }
      return value;
    }	
    case ZMQ_TCP_KEEPALIVE_INTVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL value: {}", errno);
      }
      return value;
    }
    case ZMQ_TCP_ACCEPT_FILTER:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_ACCEPT_FILTER value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }
    case ZMQ_FD:
    {
      return Resource(req::make<ZMQFd>(Object(this_)));
    }
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

/*
  Set a socket option
*/
Object HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocket>(this_);
  int status;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  
    case ZMQ_SNDHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDHWM option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVHWM option: {}", errno);
      }
      break;
    }
    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", errno);
      }
      break;
    }
    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", errno);
      }
      break;
    }
    case ZMQ_RATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", errno);
      }
      break;
    }
    case ZMQ_RECOVERY_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_SNDBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", errno);
      }
      break;
    }
    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", errno);
      }
      break;
    }
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: {}", errno);
      }
      break;
    }
    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_TYPE:
      throwSocketException("Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwSocketException("Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_SNDTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: {}", errno);
      }
      break;
    }
    case ZMQ_IPV4ONLY:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_IPV4ONLY option: {}", errno);
      }
      break;
    }
    case ZMQ_LAST_ENDPOINT:
      throwSocketException("Setting ZMQ::SOCKOPT_LAST_ENDPOINT is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_TCP_KEEPALIVE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE option: {}", errno);
      }
      break;
    }
    case ZMQ_TCP_KEEPALIVE_IDLE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE option: {}", errno);
      }
      break;
    }
    case ZMQ_TCP_KEEPALIVE_CNT:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT option: {}", errno);
      }
      break;
    }
    case ZMQ_TCP_KEEPALIVE_INTVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL option: {}", errno);
      }
      break;
    }
    case ZMQ_TCP_ACCEPT_FILTER:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_ACCEPT_FILTER option: {}", errno);
      }
      break;
    }
    case ZMQ_HWM:
    {
      int64_t iVal = pz_value.toInt64();
      int value = (int)iVal;

      if (iVal < 0) {
        throwSocketException("The option must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
      
      status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

      if (status == 0) {
        status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
      }
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", errno);
      }
      break;
    }
  
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return Object(Native::object(intern));
}

static const StaticString
  s_ZMQ("ZMQ"),
  s_SOCKOPT_HWM("SOCKOPT_HWM"),
  s_SOCKOPT_SNDHWM("SOCKOPT_SNDHWM"),
  s_SOCKOPT_RCVHWM("SOCKOPT_RCVHWM"),
  s_SOCKOPT_AFFINITY("SOCKOPT_AFFINITY"),
  s_SOCKOPT_IDENTITY("SOCKOPT_IDENTITY"),
  s_SOCKOPT_RATE("SOCKOPT_RATE"),
  s_SOCKOPT_RECOVERY_IVL("SOCKOPT_RECOVERY_IVL"),
  s_SOCKOPT_SNDBUF("SOCKOPT_SNDBUF"),
  s_SOCKOPT_RCVBUF("SOCKOPT_RCVBUF"),
  s_SOCKOPT_LINGER("SOCKOPT_LINGER"),
  s_SOCKOPT_RECONNECT_IVL("SOCKOPT_RECONNECT_IVL"),
  s_SOCKOPT_RECONNECT_IVL_MAX("SOCKOPT_RECONNECT_IVL_MAX"),
  s_SOCKOPT_BACKLOG("SOCKOPT_BACKLOG"),
  s_SOCKOPT_MAXMSGSIZE("SOCKOPT_MAXMSGSIZE"),
  s_SOCKOPT_SUBSCRIBE("SOCKOPT_SUBSCRIBE"),
  s_SOCKOPT_UNSUBSCRIBE("SOCKOPT_UNSUBSCRIBE"),
  s_SOCKOPT_TYPE("SOCKOPT_TYPE"),
  s_SOCKOPT_RCVMORE("SOCKOPT_RCVMORE"),
  s_SOCKOPT_FD("SOCKOPT_FD"),
  s_SOCKOPT_EVENTS("SOCKOPT_EVENTS"),
  s_SOCKOPT_SNDTIMEO("SOCKOPT_SNDTIMEO"),
  s_SOCKOPT_RCVTIMEO("SOCKOPT_RCVTIMEO"),
  s_SOCKOPT_IPV4ONLY("SOCKOPT_IPV4ONLY"),
  s_SOCKOPT_LAST_ENDPOINT("SOCKOPT_LAST_ENDPOINT"),
  s_SOCKOPT_TCP_KEEPALIVE("SOCKOPT_TCP_KEEPALIVE"),
  s_SOCKOPT_TCP_KEEPALIVE_IDLE("SOCKOPT_TCP_KEEPALIVE_IDLE"),
  s_SOCKOPT_TCP_KEEPALIVE_CNT("SOCKOPT_TCP_KEEPALIVE_CNT"),
  s_SOCKOPT_TCP_KEEPALIVE_INTVL("SOCKOPT_TCP_KEEPALIVE_INTVL"),
  s_SOCKOPT_TCP_ACCEPT_FILTER("SOCKOPT_TCP_ACCEPT_FILTER");

void ZMQExtension::registerSockoptConstants()
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_SOCKOPT_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(HWM, ZMQ_HWM);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDHWM, ZMQ_SNDHWM);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVHWM, ZMQ_RCVHWM);
  PHP_ZMQ_REGISTER_SOCKOPT(AFFINITY, ZMQ_AFFINITY);
  PHP_ZMQ_REGISTER_SOCKOPT(IDENTITY, ZMQ_IDENTITY);
  PHP_ZMQ_REGISTER_SOCKOPT(RATE, ZMQ_RATE);
  PHP_ZMQ_REGISTER_SOCKOPT(RECOVERY_IVL, ZMQ_RECOVERY_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDBUF, ZMQ_SNDBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVBUF, ZMQ_RCVBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(LINGER, ZMQ_LINGER);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL, ZMQ_RECONNECT_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
  PHP_ZMQ_REGISTER_SOCKOPT(BACKLOG, ZMQ_BACKLOG);
  PHP_ZMQ_REGISTER_SOCKOPT(MAXMSGSIZE, ZMQ_MAXMSGSIZE);
  PHP_ZMQ_REGISTER_SOCKOPT(SUBSCRIBE, ZMQ_SUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(TYPE, ZMQ_TYPE);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVMORE, ZMQ_RCVMORE);
  PHP_ZMQ_REGISTER_SOCKOPT(FD, ZMQ_FD);
  PHP_ZMQ_REGISTER_SOCKOPT(EVENTS, ZMQ_EVENTS);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDTIMEO, ZMQ_SNDTIMEO);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVTIMEO, ZMQ_RCVTIMEO);
  PHP_ZMQ_REGISTER_SOCKOPT(IPV4ONLY, ZMQ_IPV4ONLY);
  PHP_ZMQ_REGISTER_SOCKOPT(LAST_ENDPOINT, ZMQ_LAST_ENDPOINT);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_KEEPALIVE, ZMQ_TCP_KEEPALIVE);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_KEEPALIVE_IDLE, ZMQ_TCP_KEEPALIVE_IDLE);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_KEEPALIVE_CNT, ZMQ_TCP_KEEPALIVE_CNT);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_KEEPALIVE_INTVL, ZMQ_TCP_KEEPALIVE_INTVL);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_ACCEPT_FILTER, ZMQ_TCP_ACCEPT_FILTER);
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

#if (ZMQ_VERSION_MAJOR == 3 && ((ZMQ_VERSION_MINOR == 2 && ZMQ_VERSION_PATCH > 0) || (ZMQ_VERSION_MINOR > 2)))

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocket>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  	
    case ZMQ_SNDHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDHWM value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVHWM value: {}", errno);
      }
      return value;
    }	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", errno);
      }
      return value;
    }
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }	
    case ZMQ_RATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECOVERY_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", errno);
      }
      return value;
    }	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", errno);
      }
      return value;
    }	
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: {}", errno);
      }
      return value;
    }
    case ZMQ_SUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVMORE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_EVENTS:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: {}", errno);
      }
      return value;
    }	
    case ZMQ_IPV4ONLY:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_IPV4ONLY value: {}", errno);
      }
      return value;
    }
    case ZMQ_LAST_ENDPOINT:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_LAST_ENDPOINT value: {}", errno);
      }
      return String(value, value_len - 1, CopyString);
    }	
    case ZMQ_TCP_KEEPALIVE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_TCP_KEEPALIVE_IDLE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_TCP_KEEPALIVE_CNT:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT value: {}", errno);
      }
      return value;
    }	
    case ZMQ_TCP_KEEPALIVE_INTVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL value: {}", errno);
      }
      return value;
    }
    case ZMQ_TCP_ACCEPT_FILTER:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_ACCEPT_FILTER value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }	
    case ZMQ_DELAY_ATTACH_ON_CONNECT:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_DELAY_ATTACH_ON_CONNECT value: {}", errno);
      }
      return value;
    }	
    case ZMQ_XPUB_VERBOSE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_XPUB_VERBOSE value: {}", errno);
      }
      return value;
    }
    case ZMQ_ROUTER_MANDATORY:
      throwSocketException("Getting ZMQ::SOCKOPT_ROUTER_MANDATORY is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_FD:
    {
      return Resource(req::make<ZMQFd>(Object(this_)));
    }
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

/*
  Set a socket option
*/
Object HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocket>(this_);
  int status;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  
    case ZMQ_SNDHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDHWM option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVHWM option: {}", errno);
      }
      break;
    }
    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", errno);
      }
      break;
    }
    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", errno);
      }
      break;
    }
    case ZMQ_RATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", errno);
      }
      break;
    }
    case ZMQ_RECOVERY_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_SNDBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", errno);
      }
      break;
    }
    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", errno);
      }
      break;
    }
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: {}", errno);
      }
      break;
    }
    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_TYPE:
      throwSocketException("Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwSocketException("Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_SNDTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: {}", errno);
      }
      break;
    }
    case ZMQ_IPV4ONLY:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_IPV4ONLY option: {}", errno);
      }
      break;
    }
    case ZMQ_LAST_ENDPOINT:
      throwSocketException("Setting ZMQ::SOCKOPT_LAST_ENDPOINT is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_TCP_KEEPALIVE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE option: {}", errno);
      }
      break;
    }
    case ZMQ_TCP_KEEPALIVE_IDLE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE option: {}", errno);
      }
      break;
    }
    case ZMQ_TCP_KEEPALIVE_CNT:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT option: {}", errno);
      }
      break;
    }
    case ZMQ_TCP_KEEPALIVE_INTVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL option: {}", errno);
      }
      break;
    }
    case ZMQ_TCP_ACCEPT_FILTER:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_ACCEPT_FILTER option: {}", errno);
      }
      break;
    }
    case ZMQ_DELAY_ATTACH_ON_CONNECT:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_DELAY_ATTACH_ON_CONNECT option: {}", errno);
      }
      break;
    }
    case ZMQ_XPUB_VERBOSE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_XPUB_VERBOSE option: {}", errno);
      }
      break;
    }
    case ZMQ_ROUTER_MANDATORY:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_ROUTER_MANDATORY option: {}", errno);
      }
      break;
    }
    case ZMQ_HWM:
    {
      int64_t iVal = pz_value.toInt64();
      int value = (int)iVal;

      if (iVal < 0) {
        throwSocketException("The option must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
      
      status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

      if (status == 0) {
        status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
      }
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", errno);
      }
      break;
    }
  
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return Object(Native::object(intern));
}

static const StaticString
  s_ZMQ("ZMQ"),
  s_SOCKOPT_HWM("SOCKOPT_HWM"),
  s_SOCKOPT_SNDHWM("SOCKOPT_SNDHWM"),
  s_SOCKOPT_RCVHWM("SOCKOPT_RCVHWM"),
  s_SOCKOPT_AFFINITY("SOCKOPT_AFFINITY"),
  s_SOCKOPT_IDENTITY("SOCKOPT_IDENTITY"),
  s_SOCKOPT_RATE("SOCKOPT_RATE"),
  s_SOCKOPT_RECOVERY_IVL("SOCKOPT_RECOVERY_IVL"),
  s_SOCKOPT_SNDBUF("SOCKOPT_SNDBUF"),
  s_SOCKOPT_RCVBUF("SOCKOPT_RCVBUF"),
  s_SOCKOPT_LINGER("SOCKOPT_LINGER"),
  s_SOCKOPT_RECONNECT_IVL("SOCKOPT_RECONNECT_IVL"),
  s_SOCKOPT_RECONNECT_IVL_MAX("SOCKOPT_RECONNECT_IVL_MAX"),
  s_SOCKOPT_BACKLOG("SOCKOPT_BACKLOG"),
  s_SOCKOPT_MAXMSGSIZE("SOCKOPT_MAXMSGSIZE"),
  s_SOCKOPT_SUBSCRIBE("SOCKOPT_SUBSCRIBE"),
  s_SOCKOPT_UNSUBSCRIBE("SOCKOPT_UNSUBSCRIBE"),
  s_SOCKOPT_TYPE("SOCKOPT_TYPE"),
  s_SOCKOPT_RCVMORE("SOCKOPT_RCVMORE"),
  s_SOCKOPT_FD("SOCKOPT_FD"),
  s_SOCKOPT_EVENTS("SOCKOPT_EVENTS"),
  s_SOCKOPT_SNDTIMEO("SOCKOPT_SNDTIMEO"),
  s_SOCKOPT_RCVTIMEO("SOCKOPT_RCVTIMEO"),
  s_SOCKOPT_IPV4ONLY("SOCKOPT_IPV4ONLY"),
  s_SOCKOPT_LAST_ENDPOINT("SOCKOPT_LAST_ENDPOINT"),
  s_SOCKOPT_TCP_KEEPALIVE("SOCKOPT_TCP_KEEPALIVE"),
  s_SOCKOPT_TCP_KEEPALIVE_IDLE("SOCKOPT_TCP_KEEPALIVE_IDLE"),
  s_SOCKOPT_TCP_KEEPALIVE_CNT("SOCKOPT_TCP_KEEPALIVE_CNT"),
  s_SOCKOPT_TCP_KEEPALIVE_INTVL("SOCKOPT_TCP_KEEPALIVE_INTVL"),
  s_SOCKOPT_TCP_ACCEPT_FILTER("SOCKOPT_TCP_ACCEPT_FILTER"),
  s_SOCKOPT_DELAY_ATTACH_ON_CONNECT("SOCKOPT_DELAY_ATTACH_ON_CONNECT"),
  s_SOCKOPT_XPUB_VERBOSE("SOCKOPT_XPUB_VERBOSE"),
  s_SOCKOPT_ROUTER_MANDATORY("SOCKOPT_ROUTER_MANDATORY");

void ZMQExtension::registerSockoptConstants()
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_SOCKOPT_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(HWM, ZMQ_HWM);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDHWM, ZMQ_SNDHWM);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVHWM, ZMQ_RCVHWM);
  PHP_ZMQ_REGISTER_SOCKOPT(AFFINITY, ZMQ_AFFINITY);
  PHP_ZMQ_REGISTER_SOCKOPT(IDENTITY, ZMQ_IDENTITY);
  PHP_ZMQ_REGISTER_SOCKOPT(RATE, ZMQ_RATE);
  PHP_ZMQ_REGISTER_SOCKOPT(RECOVERY_IVL, ZMQ_RECOVERY_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDBUF, ZMQ_SNDBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVBUF, ZMQ_RCVBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(LINGER, ZMQ_LINGER);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL, ZMQ_RECONNECT_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
  PHP_ZMQ_REGISTER_SOCKOPT(BACKLOG, ZMQ_BACKLOG);
  PHP_ZMQ_REGISTER_SOCKOPT(MAXMSGSIZE, ZMQ_MAXMSGSIZE);
  PHP_ZMQ_REGISTER_SOCKOPT(SUBSCRIBE, ZMQ_SUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(TYPE, ZMQ_TYPE);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVMORE, ZMQ_RCVMORE);
  PHP_ZMQ_REGISTER_SOCKOPT(FD, ZMQ_FD);
  PHP_ZMQ_REGISTER_SOCKOPT(EVENTS, ZMQ_EVENTS);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDTIMEO, ZMQ_SNDTIMEO);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVTIMEO, ZMQ_RCVTIMEO);
  PHP_ZMQ_REGISTER_SOCKOPT(IPV4ONLY, ZMQ_IPV4ONLY);
  PHP_ZMQ_REGISTER_SOCKOPT(LAST_ENDPOINT, ZMQ_LAST_ENDPOINT);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_KEEPALIVE, ZMQ_TCP_KEEPALIVE);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_KEEPALIVE_IDLE, ZMQ_TCP_KEEPALIVE_IDLE);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_KEEPALIVE_CNT, ZMQ_TCP_KEEPALIVE_CNT);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_KEEPALIVE_INTVL, ZMQ_TCP_KEEPALIVE_INTVL);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_ACCEPT_FILTER, ZMQ_TCP_ACCEPT_FILTER);
  PHP_ZMQ_REGISTER_SOCKOPT(DELAY_ATTACH_ON_CONNECT, ZMQ_DELAY_ATTACH_ON_CONNECT);
  PHP_ZMQ_REGISTER_SOCKOPT(XPUB_VERBOSE, ZMQ_XPUB_VERBOSE);
  PHP_ZMQ_REGISTER_SOCKOPT(ROUTER_MANDATORY, ZMQ_ROUTER_MANDATORY);
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

#if ZMQ_VERSION_MAJOR >= 4

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocket>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  	
    case ZMQ_SNDHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDHWM value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVHWM value: {}", errno);
      }
      return value;
    }	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", errno);
      }
      return value;
    }
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }	
    case ZMQ_RATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECOVERY_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", errno);
      }
      return value;
    }	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", errno);
      }
      return value;
    }	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", errno);
      }
      return value;
    }	
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: {}", errno);
      }
      return value;
    }
    case ZMQ_SUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwSocketException("Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVMORE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_EVENTS:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", errno);
      }
      return value;
    }	
    case ZMQ_SNDTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: {}", errno);
      }
      return value;
    }	
    case ZMQ_RCVTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: {}", errno);
      }
      return value;
    }	
    case ZMQ_IPV4ONLY:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_IPV4ONLY value: {}", errno);
      }
      return value;
    }
    case ZMQ_LAST_ENDPOINT:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_LAST_ENDPOINT value: {}", errno);
      }
      return String(value, value_len - 1, CopyString);
    }	
    case ZMQ_TCP_KEEPALIVE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_TCP_KEEPALIVE_IDLE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_TCP_KEEPALIVE_CNT:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT value: {}", errno);
      }
      return value;
    }	
    case ZMQ_TCP_KEEPALIVE_INTVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL value: {}", errno);
      }
      return value;
    }
    case ZMQ_TCP_ACCEPT_FILTER:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_TCP_ACCEPT_FILTER value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }	
    case ZMQ_DELAY_ATTACH_ON_CONNECT:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_DELAY_ATTACH_ON_CONNECT value: {}", errno);
      }
      return value;
    }	
    case ZMQ_XPUB_VERBOSE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_XPUB_VERBOSE value: {}", errno);
      }
      return value;
    }
    case ZMQ_ROUTER_MANDATORY:
      throwSocketException("Getting ZMQ::SOCKOPT_ROUTER_MANDATORY is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_ROUTER_RAW:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_ROUTER_RAW value: {}", errno);
      }
      return value;
    }	
    case ZMQ_IPV6:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_IPV6 value: {}", errno);
      }
      return value;
    }	
    case ZMQ_PLAIN_SERVER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_PLAIN_SERVER value: {}", errno);
      }
      return value;
    }
    case ZMQ_PLAIN_USERNAME:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_PLAIN_USERNAME value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }
    case ZMQ_PLAIN_PASSWORD:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_PLAIN_PASSWORD value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }	
    case ZMQ_CURVE_SERVER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_CURVE_SERVER value: {}", errno);
      }
      return value;
    }
    case ZMQ_CURVE_PUBLICKEY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_CURVE_PUBLICKEY value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }
    case ZMQ_CURVE_SECRETKEY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_CURVE_SECRETKEY value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }
    case ZMQ_CURVE_SERVERKEY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_CURVE_SERVERKEY value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }	
    case ZMQ_PROBE_ROUTER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_PROBE_ROUTER value: {}", errno);
      }
      return value;
    }	
    case ZMQ_REQ_CORRELATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_REQ_CORRELATE value: {}", errno);
      }
      return value;
    }	
    case ZMQ_REQ_RELAXED:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_REQ_RELAXED value: {}", errno);
      }
      return value;
    }	
    case ZMQ_CONFLATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_CONFLATE value: {}", errno);
      }
      return value;
    }
    case ZMQ_ZAP_DOMAIN:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwSocketExceptionZMQErr("Failed to get the option ZMQ::SOCKOPT_ZAP_DOMAIN value: {}", errno);
      }
      return String(value, value_len, CopyString);
    }
    case ZMQ_FD:
    {
      return Resource(req::make<ZMQFd>(Object(this_)));
    }
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

/*
  Set a socket option
*/
Object HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocket>(this_);
  int status;

  if (!intern->socket) {
    throwSocketException("The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {
  
    case ZMQ_SNDHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDHWM option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVHWM option: {}", errno);
      }
      break;
    }
    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwSocketException("The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", errno);
      }
      break;
    }
    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", errno);
      }
      break;
    }
    case ZMQ_RATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", errno);
      }
      break;
    }
    case ZMQ_RECOVERY_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_SNDBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", errno);
      }
      break;
    }
    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", errno);
      }
      break;
    }
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", errno);
      }
      break;
    }
    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", errno);
      }
      break;
    }
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: {}", errno);
      }
      break;
    }
    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", errno);
      }
      break;
    }
    case ZMQ_TYPE:
      throwSocketException("Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwSocketException("Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_SNDTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: {}", errno);
      }
      break;
    }
    case ZMQ_RCVTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: {}", errno);
      }
      break;
    }
    case ZMQ_IPV4ONLY:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_IPV4ONLY option: {}", errno);
      }
      break;
    }
    case ZMQ_LAST_ENDPOINT:
      throwSocketException("Setting ZMQ::SOCKOPT_LAST_ENDPOINT is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_TCP_KEEPALIVE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE option: {}", errno);
      }
      break;
    }
    case ZMQ_TCP_KEEPALIVE_IDLE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE option: {}", errno);
      }
      break;
    }
    case ZMQ_TCP_KEEPALIVE_CNT:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT option: {}", errno);
      }
      break;
    }
    case ZMQ_TCP_KEEPALIVE_INTVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL option: {}", errno);
      }
      break;
    }
    case ZMQ_TCP_ACCEPT_FILTER:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_TCP_ACCEPT_FILTER option: {}", errno);
      }
      break;
    }
    case ZMQ_DELAY_ATTACH_ON_CONNECT:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_DELAY_ATTACH_ON_CONNECT option: {}", errno);
      }
      break;
    }
    case ZMQ_XPUB_VERBOSE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_XPUB_VERBOSE option: {}", errno);
      }
      break;
    }
    case ZMQ_ROUTER_MANDATORY:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_ROUTER_MANDATORY option: {}", errno);
      }
      break;
    }
    case ZMQ_ROUTER_RAW:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_ROUTER_RAW option: {}", errno);
      }
      break;
    }
    case ZMQ_IPV6:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_IPV6 option: {}", errno);
      }
      break;
    }
    case ZMQ_PLAIN_SERVER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_PLAIN_SERVER option: {}", errno);
      }
      break;
    }
    case ZMQ_PLAIN_USERNAME:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_PLAIN_USERNAME option: {}", errno);
      }
      break;
    }
    case ZMQ_PLAIN_PASSWORD:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_PLAIN_PASSWORD option: {}", errno);
      }
      break;
    }
    case ZMQ_CURVE_SERVER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_CURVE_SERVER option: {}", errno);
      }
      break;
    }
    case ZMQ_CURVE_PUBLICKEY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_CURVE_PUBLICKEY option: {}", errno);
      }
      break;
    }
    case ZMQ_CURVE_SECRETKEY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_CURVE_SECRETKEY option: {}", errno);
      }
      break;
    }
    case ZMQ_CURVE_SERVERKEY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_CURVE_SERVERKEY option: {}", errno);
      }
      break;
    }
    case ZMQ_PROBE_ROUTER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_PROBE_ROUTER option: {}", errno);
      }
      break;
    }
    case ZMQ_REQ_CORRELATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_REQ_CORRELATE option: {}", errno);
      }
      break;
    }
    case ZMQ_REQ_RELAXED:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_REQ_RELAXED option: {}", errno);
      }
      break;
    }
    case ZMQ_CONFLATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_CONFLATE option: {}", errno);
      }
      break;
    }
    case ZMQ_ZAP_DOMAIN:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_ZAP_DOMAIN option: {}", errno);
      }
      break;
    }
    case ZMQ_HWM:
    {
      int64_t iVal = pz_value.toInt64();
      int value = (int)iVal;

      if (iVal < 0) {
        throwSocketException("The option must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
      
      status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

      if (status == 0) {
        status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
      }
      
      if (status != 0) {
        throwSocketExceptionZMQErr("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", errno);
      }
      break;
    }
  
    default:
      throwSocketException("Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return Object(Native::object(intern));
}

static const StaticString
  s_ZMQ("ZMQ"),
  s_SOCKOPT_HWM("SOCKOPT_HWM"),
  s_SOCKOPT_SNDHWM("SOCKOPT_SNDHWM"),
  s_SOCKOPT_RCVHWM("SOCKOPT_RCVHWM"),
  s_SOCKOPT_AFFINITY("SOCKOPT_AFFINITY"),
  s_SOCKOPT_IDENTITY("SOCKOPT_IDENTITY"),
  s_SOCKOPT_RATE("SOCKOPT_RATE"),
  s_SOCKOPT_RECOVERY_IVL("SOCKOPT_RECOVERY_IVL"),
  s_SOCKOPT_SNDBUF("SOCKOPT_SNDBUF"),
  s_SOCKOPT_RCVBUF("SOCKOPT_RCVBUF"),
  s_SOCKOPT_LINGER("SOCKOPT_LINGER"),
  s_SOCKOPT_RECONNECT_IVL("SOCKOPT_RECONNECT_IVL"),
  s_SOCKOPT_RECONNECT_IVL_MAX("SOCKOPT_RECONNECT_IVL_MAX"),
  s_SOCKOPT_BACKLOG("SOCKOPT_BACKLOG"),
  s_SOCKOPT_MAXMSGSIZE("SOCKOPT_MAXMSGSIZE"),
  s_SOCKOPT_SUBSCRIBE("SOCKOPT_SUBSCRIBE"),
  s_SOCKOPT_UNSUBSCRIBE("SOCKOPT_UNSUBSCRIBE"),
  s_SOCKOPT_TYPE("SOCKOPT_TYPE"),
  s_SOCKOPT_RCVMORE("SOCKOPT_RCVMORE"),
  s_SOCKOPT_FD("SOCKOPT_FD"),
  s_SOCKOPT_EVENTS("SOCKOPT_EVENTS"),
  s_SOCKOPT_SNDTIMEO("SOCKOPT_SNDTIMEO"),
  s_SOCKOPT_RCVTIMEO("SOCKOPT_RCVTIMEO"),
  s_SOCKOPT_IPV4ONLY("SOCKOPT_IPV4ONLY"),
  s_SOCKOPT_LAST_ENDPOINT("SOCKOPT_LAST_ENDPOINT"),
  s_SOCKOPT_TCP_KEEPALIVE("SOCKOPT_TCP_KEEPALIVE"),
  s_SOCKOPT_TCP_KEEPALIVE_IDLE("SOCKOPT_TCP_KEEPALIVE_IDLE"),
  s_SOCKOPT_TCP_KEEPALIVE_CNT("SOCKOPT_TCP_KEEPALIVE_CNT"),
  s_SOCKOPT_TCP_KEEPALIVE_INTVL("SOCKOPT_TCP_KEEPALIVE_INTVL"),
  s_SOCKOPT_TCP_ACCEPT_FILTER("SOCKOPT_TCP_ACCEPT_FILTER"),
  s_SOCKOPT_DELAY_ATTACH_ON_CONNECT("SOCKOPT_DELAY_ATTACH_ON_CONNECT"),
  s_SOCKOPT_XPUB_VERBOSE("SOCKOPT_XPUB_VERBOSE"),
  s_SOCKOPT_ROUTER_MANDATORY("SOCKOPT_ROUTER_MANDATORY"),
  s_SOCKOPT_ROUTER_RAW("SOCKOPT_ROUTER_RAW"),
  s_SOCKOPT_IPV6("SOCKOPT_IPV6"),
  s_SOCKOPT_PLAIN_SERVER("SOCKOPT_PLAIN_SERVER"),
  s_SOCKOPT_PLAIN_USERNAME("SOCKOPT_PLAIN_USERNAME"),
  s_SOCKOPT_PLAIN_PASSWORD("SOCKOPT_PLAIN_PASSWORD"),
  s_SOCKOPT_CURVE_SERVER("SOCKOPT_CURVE_SERVER"),
  s_SOCKOPT_CURVE_PUBLICKEY("SOCKOPT_CURVE_PUBLICKEY"),
  s_SOCKOPT_CURVE_SECRETKEY("SOCKOPT_CURVE_SECRETKEY"),
  s_SOCKOPT_CURVE_SERVERKEY("SOCKOPT_CURVE_SERVERKEY"),
  s_SOCKOPT_PROBE_ROUTER("SOCKOPT_PROBE_ROUTER"),
  s_SOCKOPT_REQ_CORRELATE("SOCKOPT_REQ_CORRELATE"),
  s_SOCKOPT_REQ_RELAXED("SOCKOPT_REQ_RELAXED"),
  s_SOCKOPT_CONFLATE("SOCKOPT_CONFLATE"),
  s_SOCKOPT_ZAP_DOMAIN("SOCKOPT_ZAP_DOMAIN");

void ZMQExtension::registerSockoptConstants()
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_SOCKOPT_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(HWM, ZMQ_HWM);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDHWM, ZMQ_SNDHWM);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVHWM, ZMQ_RCVHWM);
  PHP_ZMQ_REGISTER_SOCKOPT(AFFINITY, ZMQ_AFFINITY);
  PHP_ZMQ_REGISTER_SOCKOPT(IDENTITY, ZMQ_IDENTITY);
  PHP_ZMQ_REGISTER_SOCKOPT(RATE, ZMQ_RATE);
  PHP_ZMQ_REGISTER_SOCKOPT(RECOVERY_IVL, ZMQ_RECOVERY_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDBUF, ZMQ_SNDBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVBUF, ZMQ_RCVBUF);
  PHP_ZMQ_REGISTER_SOCKOPT(LINGER, ZMQ_LINGER);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL, ZMQ_RECONNECT_IVL);
  PHP_ZMQ_REGISTER_SOCKOPT(RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
  PHP_ZMQ_REGISTER_SOCKOPT(BACKLOG, ZMQ_BACKLOG);
  PHP_ZMQ_REGISTER_SOCKOPT(MAXMSGSIZE, ZMQ_MAXMSGSIZE);
  PHP_ZMQ_REGISTER_SOCKOPT(SUBSCRIBE, ZMQ_SUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
  PHP_ZMQ_REGISTER_SOCKOPT(TYPE, ZMQ_TYPE);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVMORE, ZMQ_RCVMORE);
  PHP_ZMQ_REGISTER_SOCKOPT(FD, ZMQ_FD);
  PHP_ZMQ_REGISTER_SOCKOPT(EVENTS, ZMQ_EVENTS);
  PHP_ZMQ_REGISTER_SOCKOPT(SNDTIMEO, ZMQ_SNDTIMEO);
  PHP_ZMQ_REGISTER_SOCKOPT(RCVTIMEO, ZMQ_RCVTIMEO);
  PHP_ZMQ_REGISTER_SOCKOPT(IPV4ONLY, ZMQ_IPV4ONLY);
  PHP_ZMQ_REGISTER_SOCKOPT(LAST_ENDPOINT, ZMQ_LAST_ENDPOINT);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_KEEPALIVE, ZMQ_TCP_KEEPALIVE);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_KEEPALIVE_IDLE, ZMQ_TCP_KEEPALIVE_IDLE);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_KEEPALIVE_CNT, ZMQ_TCP_KEEPALIVE_CNT);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_KEEPALIVE_INTVL, ZMQ_TCP_KEEPALIVE_INTVL);
  PHP_ZMQ_REGISTER_SOCKOPT(TCP_ACCEPT_FILTER, ZMQ_TCP_ACCEPT_FILTER);
  PHP_ZMQ_REGISTER_SOCKOPT(DELAY_ATTACH_ON_CONNECT, ZMQ_DELAY_ATTACH_ON_CONNECT);
  PHP_ZMQ_REGISTER_SOCKOPT(XPUB_VERBOSE, ZMQ_XPUB_VERBOSE);
  PHP_ZMQ_REGISTER_SOCKOPT(ROUTER_MANDATORY, ZMQ_ROUTER_MANDATORY);
  PHP_ZMQ_REGISTER_SOCKOPT(ROUTER_RAW, ZMQ_ROUTER_RAW);
  PHP_ZMQ_REGISTER_SOCKOPT(IPV6, ZMQ_IPV6);
  PHP_ZMQ_REGISTER_SOCKOPT(PLAIN_SERVER, ZMQ_PLAIN_SERVER);
  PHP_ZMQ_REGISTER_SOCKOPT(PLAIN_USERNAME, ZMQ_PLAIN_USERNAME);
  PHP_ZMQ_REGISTER_SOCKOPT(PLAIN_PASSWORD, ZMQ_PLAIN_PASSWORD);
  PHP_ZMQ_REGISTER_SOCKOPT(CURVE_SERVER, ZMQ_CURVE_SERVER);
  PHP_ZMQ_REGISTER_SOCKOPT(CURVE_PUBLICKEY, ZMQ_CURVE_PUBLICKEY);
  PHP_ZMQ_REGISTER_SOCKOPT(CURVE_SECRETKEY, ZMQ_CURVE_SECRETKEY);
  PHP_ZMQ_REGISTER_SOCKOPT(CURVE_SERVERKEY, ZMQ_CURVE_SERVERKEY);
  PHP_ZMQ_REGISTER_SOCKOPT(PROBE_ROUTER, ZMQ_PROBE_ROUTER);
  PHP_ZMQ_REGISTER_SOCKOPT(REQ_CORRELATE, ZMQ_REQ_CORRELATE);
  PHP_ZMQ_REGISTER_SOCKOPT(REQ_RELAXED, ZMQ_REQ_RELAXED);
  PHP_ZMQ_REGISTER_SOCKOPT(CONFLATE, ZMQ_CONFLATE);
  PHP_ZMQ_REGISTER_SOCKOPT(ZAP_DOMAIN, ZMQ_ZAP_DOMAIN);
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

}}
  