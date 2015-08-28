
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

#include <folly/Format.h>

namespace HPHP { namespace zmq {
  
#if ZMQ_VERSION_MAJOR == 2 && ZMQ_VERSION_MINOR < 2

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  	
    case ZMQ_HWM:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_HWM value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SWAP:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SWAP value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  	
    case ZMQ_RATE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECOVERY_IVL:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECOVERY_IVL_MSEC:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL_MSEC value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_MCAST_LOOP:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_MCAST_LOOP value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDBUF:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVBUF:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_SUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVMORE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_EVENTS:
    {
      uint32_t value;
      value_len = sizeof(uint32_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  

    case ZMQ_FD:
    {
      php_stream *stm = php_zmq_create_zmq_fd(getThis());
      if (stm) {
        php_stream_to_zval(stm, return_value);
        return;
      }
      return false;
    }
    break;

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

  

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
  Set a socket option
*/
ZMQSocket* HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  int status;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  

    case ZMQ_HWM:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_HWM value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SWAP:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SWAP option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RATE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECOVERY_IVL:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECOVERY_IVL_MSEC:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL_MSEC option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_MCAST_LOOP:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_MCAST_LOOP option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SNDBUF:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_SNDBUF value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVBUF:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_RCVBUF value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    case ZMQ_TYPE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return intern;
}

  

void ZMQExtension::registerSockoptConstants()
{
  static const StaticString s_ZMQ("ZMQ");
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  static const StaticString s_##const_name("const_name"); \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_HWM, ZMQ_HWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SWAP, ZMQ_SWAP);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_AFFINITY, ZMQ_AFFINITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_IDENTITY, ZMQ_IDENTITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RATE, ZMQ_RATE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECOVERY_IVL, ZMQ_RECOVERY_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECOVERY_IVL_MSEC, ZMQ_RECOVERY_IVL_MSEC);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_MCAST_LOOP, ZMQ_MCAST_LOOP);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDBUF, ZMQ_SNDBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVBUF, ZMQ_RCVBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_LINGER, ZMQ_LINGER);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL, ZMQ_RECONNECT_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_BACKLOG, ZMQ_BACKLOG);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SUBSCRIBE, ZMQ_SUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TYPE, ZMQ_TYPE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVMORE, ZMQ_RCVMORE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_FD, ZMQ_FD);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_EVENTS, ZMQ_EVENTS);
      
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

#if ZMQ_VERSION_MAJOR == 2 && ZMQ_VERSION_MINOR >= 2

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  	
    case ZMQ_HWM:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_HWM value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SWAP:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SWAP value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  	
    case ZMQ_RATE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECOVERY_IVL:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECOVERY_IVL_MSEC:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL_MSEC value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_MCAST_LOOP:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_MCAST_LOOP value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDBUF:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVBUF:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_SUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVMORE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_EVENTS:
    {
      uint32_t value;
      value_len = sizeof(uint32_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  

    case ZMQ_FD:
    {
      php_stream *stm = php_zmq_create_zmq_fd(getThis());
      if (stm) {
        php_stream_to_zval(stm, return_value);
        return;
      }
      return false;
    }
    break;

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

  

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
  Set a socket option
*/
ZMQSocket* HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  int status;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  

    case ZMQ_HWM:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_HWM value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SWAP:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SWAP option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RATE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECOVERY_IVL:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECOVERY_IVL_MSEC:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL_MSEC option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_MCAST_LOOP:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_MCAST_LOOP option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SNDBUF:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_SNDBUF value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVBUF:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_RCVBUF value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    case ZMQ_TYPE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  

    case ZMQ_SNDTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return intern;
}

  

void ZMQExtension::registerSockoptConstants()
{
  static const StaticString s_ZMQ("ZMQ");
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  static const StaticString s_##const_name("const_name"); \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_HWM, ZMQ_HWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SWAP, ZMQ_SWAP);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_AFFINITY, ZMQ_AFFINITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_IDENTITY, ZMQ_IDENTITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RATE, ZMQ_RATE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECOVERY_IVL, ZMQ_RECOVERY_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECOVERY_IVL_MSEC, ZMQ_RECOVERY_IVL_MSEC);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_MCAST_LOOP, ZMQ_MCAST_LOOP);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDBUF, ZMQ_SNDBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVBUF, ZMQ_RCVBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_LINGER, ZMQ_LINGER);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL, ZMQ_RECONNECT_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_BACKLOG, ZMQ_BACKLOG);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SUBSCRIBE, ZMQ_SUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TYPE, ZMQ_TYPE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVMORE, ZMQ_RCVMORE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_FD, ZMQ_FD);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_EVENTS, ZMQ_EVENTS);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDTIMEO, ZMQ_SNDTIMEO);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVTIMEO, ZMQ_RCVTIMEO);
      
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  	
    case ZMQ_SNDHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDHWM value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVHWM value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  	
    case ZMQ_RATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECOVERY_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_SUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVMORE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_EVENTS:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVLABEL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVLABEL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  

    case ZMQ_FD:
    {
      php_stream *stm = php_zmq_create_zmq_fd(getThis());
      if (stm) {
        php_stream_to_zval(stm, return_value);
        return;
      }
      return false;
    }
    break;

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

  

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
  Set a socket option
*/
ZMQSocket* HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  int status;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  

    case ZMQ_SNDHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDHWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVHWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECOVERY_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SNDBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_MAXMSGSIZE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    case ZMQ_TYPE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  

    case ZMQ_SNDTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    case ZMQ_RCVLABEL:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_RCVLABEL is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    
    case ZMQ_HWM:
    {
      int64_t iVal = pz_value.toInt64();
      int value = (int)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
      
      status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

      if (status == 0) {
        status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
      }
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }
  

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return intern;
}

  

void ZMQExtension::registerSockoptConstants()
{
  static const StaticString s_ZMQ("ZMQ");
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  static const StaticString s_##const_name("const_name"); \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_HWM, ZMQ_HWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDHWM, ZMQ_SNDHWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVHWM, ZMQ_RCVHWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_AFFINITY, ZMQ_AFFINITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_IDENTITY, ZMQ_IDENTITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RATE, ZMQ_RATE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECOVERY_IVL, ZMQ_RECOVERY_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDBUF, ZMQ_SNDBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVBUF, ZMQ_RCVBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_LINGER, ZMQ_LINGER);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL, ZMQ_RECONNECT_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_BACKLOG, ZMQ_BACKLOG);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_MAXMSGSIZE, ZMQ_MAXMSGSIZE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SUBSCRIBE, ZMQ_SUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TYPE, ZMQ_TYPE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVMORE, ZMQ_RCVMORE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_FD, ZMQ_FD);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_EVENTS, ZMQ_EVENTS);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDTIMEO, ZMQ_SNDTIMEO);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVTIMEO, ZMQ_RCVTIMEO);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVLABEL, ZMQ_RCVLABEL);
      
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 1

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  	
    case ZMQ_SNDHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDHWM value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVHWM value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  	
    case ZMQ_RATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECOVERY_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_SUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVMORE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_EVENTS:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  

    case ZMQ_FD:
    {
      php_stream *stm = php_zmq_create_zmq_fd(getThis());
      if (stm) {
        php_stream_to_zval(stm, return_value);
        return;
      }
      return false;
    }
    break;

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

  

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
  Set a socket option
*/
ZMQSocket* HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  int status;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  

    case ZMQ_SNDHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDHWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVHWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECOVERY_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SNDBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_MAXMSGSIZE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    case ZMQ_TYPE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  

    case ZMQ_SNDTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    
    case ZMQ_HWM:
    {
      int64_t iVal = pz_value.toInt64();
      int value = (int)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
      
      status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

      if (status == 0) {
        status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
      }
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }
  

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return intern;
}

  

void ZMQExtension::registerSockoptConstants()
{
  static const StaticString s_ZMQ("ZMQ");
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  static const StaticString s_##const_name("const_name"); \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_HWM, ZMQ_HWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDHWM, ZMQ_SNDHWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVHWM, ZMQ_RCVHWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_AFFINITY, ZMQ_AFFINITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_IDENTITY, ZMQ_IDENTITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RATE, ZMQ_RATE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECOVERY_IVL, ZMQ_RECOVERY_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDBUF, ZMQ_SNDBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVBUF, ZMQ_RCVBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_LINGER, ZMQ_LINGER);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL, ZMQ_RECONNECT_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_BACKLOG, ZMQ_BACKLOG);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_MAXMSGSIZE, ZMQ_MAXMSGSIZE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SUBSCRIBE, ZMQ_SUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TYPE, ZMQ_TYPE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVMORE, ZMQ_RCVMORE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_FD, ZMQ_FD);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_EVENTS, ZMQ_EVENTS);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDTIMEO, ZMQ_SNDTIMEO);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVTIMEO, ZMQ_RCVTIMEO);
      
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 2 && ZMQ_VERSION_PATCH == 0)

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  	
    case ZMQ_SNDHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDHWM value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVHWM value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  	
    case ZMQ_RATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECOVERY_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_SUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVMORE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_EVENTS:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_IPV4ONLY:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_IPV4ONLY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_LAST_ENDPOINT:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_LAST_ENDPOINT value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len - 1, CopyString);
    }
  	
    case ZMQ_TCP_KEEPALIVE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_TCP_KEEPALIVE_IDLE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_TCP_KEEPALIVE_CNT:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_TCP_KEEPALIVE_INTVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_TCP_ACCEPT_FILTER:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_ACCEPT_FILTER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  

    case ZMQ_FD:
    {
      php_stream *stm = php_zmq_create_zmq_fd(getThis());
      if (stm) {
        php_stream_to_zval(stm, return_value);
        return;
      }
      return false;
    }
    break;

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

  

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
  Set a socket option
*/
ZMQSocket* HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  int status;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  

    case ZMQ_SNDHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDHWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVHWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECOVERY_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SNDBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_MAXMSGSIZE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    case ZMQ_TYPE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  

    case ZMQ_SNDTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_IPV4ONLY:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_IPV4ONLY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    case ZMQ_LAST_ENDPOINT:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_LAST_ENDPOINT is not supported", PHP_ZMQ_INTERNAL_ERROR);
  

    case ZMQ_TCP_KEEPALIVE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_TCP_KEEPALIVE_IDLE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_TCP_KEEPALIVE_CNT:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_TCP_KEEPALIVE_INTVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_TCP_ACCEPT_FILTER:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_ACCEPT_FILTER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    
    case ZMQ_HWM:
    {
      int64_t iVal = pz_value.toInt64();
      int value = (int)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
      
      status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

      if (status == 0) {
        status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
      }
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }
  

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return intern;
}

  

void ZMQExtension::registerSockoptConstants()
{
  static const StaticString s_ZMQ("ZMQ");
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  static const StaticString s_##const_name("const_name"); \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_HWM, ZMQ_HWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDHWM, ZMQ_SNDHWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVHWM, ZMQ_RCVHWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_AFFINITY, ZMQ_AFFINITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_IDENTITY, ZMQ_IDENTITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RATE, ZMQ_RATE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECOVERY_IVL, ZMQ_RECOVERY_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDBUF, ZMQ_SNDBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVBUF, ZMQ_RCVBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_LINGER, ZMQ_LINGER);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL, ZMQ_RECONNECT_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_BACKLOG, ZMQ_BACKLOG);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_MAXMSGSIZE, ZMQ_MAXMSGSIZE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SUBSCRIBE, ZMQ_SUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TYPE, ZMQ_TYPE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVMORE, ZMQ_RCVMORE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_FD, ZMQ_FD);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_EVENTS, ZMQ_EVENTS);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDTIMEO, ZMQ_SNDTIMEO);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVTIMEO, ZMQ_RCVTIMEO);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_IPV4ONLY, ZMQ_IPV4ONLY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_LAST_ENDPOINT, ZMQ_LAST_ENDPOINT);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_KEEPALIVE, ZMQ_TCP_KEEPALIVE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_KEEPALIVE_IDLE, ZMQ_TCP_KEEPALIVE_IDLE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_KEEPALIVE_CNT, ZMQ_TCP_KEEPALIVE_CNT);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_KEEPALIVE_INTVL, ZMQ_TCP_KEEPALIVE_INTVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_ACCEPT_FILTER, ZMQ_TCP_ACCEPT_FILTER);
      
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

#if (ZMQ_VERSION_MAJOR == 3 && ((ZMQ_VERSION_MINOR == 2 && ZMQ_VERSION_PATCH > 0) || (ZMQ_VERSION_MINOR > 2)))

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  	
    case ZMQ_SNDHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDHWM value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVHWM value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  	
    case ZMQ_RATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECOVERY_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_SUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVMORE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_EVENTS:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_IPV4ONLY:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_IPV4ONLY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_LAST_ENDPOINT:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_LAST_ENDPOINT value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len - 1, CopyString);
    }
  	
    case ZMQ_TCP_KEEPALIVE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_TCP_KEEPALIVE_IDLE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_TCP_KEEPALIVE_CNT:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_TCP_KEEPALIVE_INTVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_TCP_ACCEPT_FILTER:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_ACCEPT_FILTER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  	
    case ZMQ_DELAY_ATTACH_ON_CONNECT:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_DELAY_ATTACH_ON_CONNECT value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_XPUB_VERBOSE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_XPUB_VERBOSE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_ROUTER_MANDATORY:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_ROUTER_MANDATORY is not supported", PHP_ZMQ_INTERNAL_ERROR);
  

    case ZMQ_FD:
    {
      php_stream *stm = php_zmq_create_zmq_fd(getThis());
      if (stm) {
        php_stream_to_zval(stm, return_value);
        return;
      }
      return false;
    }
    break;

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

  

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
  Set a socket option
*/
ZMQSocket* HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  int status;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  

    case ZMQ_SNDHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDHWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVHWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECOVERY_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SNDBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_MAXMSGSIZE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    case ZMQ_TYPE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  

    case ZMQ_SNDTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_IPV4ONLY:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_IPV4ONLY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    case ZMQ_LAST_ENDPOINT:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_LAST_ENDPOINT is not supported", PHP_ZMQ_INTERNAL_ERROR);
  

    case ZMQ_TCP_KEEPALIVE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_TCP_KEEPALIVE_IDLE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_TCP_KEEPALIVE_CNT:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_TCP_KEEPALIVE_INTVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_TCP_ACCEPT_FILTER:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_ACCEPT_FILTER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_DELAY_ATTACH_ON_CONNECT:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_DELAY_ATTACH_ON_CONNECT option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_XPUB_VERBOSE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_XPUB_VERBOSE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_ROUTER_MANDATORY:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_ROUTER_MANDATORY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    
    case ZMQ_HWM:
    {
      int64_t iVal = pz_value.toInt64();
      int value = (int)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
      
      status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

      if (status == 0) {
        status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
      }
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }
  

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return intern;
}

  

void ZMQExtension::registerSockoptConstants()
{
  static const StaticString s_ZMQ("ZMQ");
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  static const StaticString s_##const_name("const_name"); \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_HWM, ZMQ_HWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDHWM, ZMQ_SNDHWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVHWM, ZMQ_RCVHWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_AFFINITY, ZMQ_AFFINITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_IDENTITY, ZMQ_IDENTITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RATE, ZMQ_RATE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECOVERY_IVL, ZMQ_RECOVERY_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDBUF, ZMQ_SNDBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVBUF, ZMQ_RCVBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_LINGER, ZMQ_LINGER);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL, ZMQ_RECONNECT_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_BACKLOG, ZMQ_BACKLOG);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_MAXMSGSIZE, ZMQ_MAXMSGSIZE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SUBSCRIBE, ZMQ_SUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TYPE, ZMQ_TYPE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVMORE, ZMQ_RCVMORE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_FD, ZMQ_FD);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_EVENTS, ZMQ_EVENTS);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDTIMEO, ZMQ_SNDTIMEO);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVTIMEO, ZMQ_RCVTIMEO);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_IPV4ONLY, ZMQ_IPV4ONLY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_LAST_ENDPOINT, ZMQ_LAST_ENDPOINT);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_KEEPALIVE, ZMQ_TCP_KEEPALIVE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_KEEPALIVE_IDLE, ZMQ_TCP_KEEPALIVE_IDLE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_KEEPALIVE_CNT, ZMQ_TCP_KEEPALIVE_CNT);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_KEEPALIVE_INTVL, ZMQ_TCP_KEEPALIVE_INTVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_ACCEPT_FILTER, ZMQ_TCP_ACCEPT_FILTER);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_DELAY_ATTACH_ON_CONNECT, ZMQ_DELAY_ATTACH_ON_CONNECT);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_XPUB_VERBOSE, ZMQ_XPUB_VERBOSE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_ROUTER_MANDATORY, ZMQ_ROUTER_MANDATORY);
      
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

#if ZMQ_VERSION_MAJOR >= 4

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  size_t value_len;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  	
    case ZMQ_SNDHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDHWM value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVHWM:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVHWM value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_AFFINITY:
    {
      uint64_t value;
      value_len = sizeof(uint64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_AFFINITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_IDENTITY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_IDENTITY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  	
    case ZMQ_RATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RATE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECOVERY_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVBUF:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVBUF value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_LINGER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_LINGER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_BACKLOG:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_BACKLOG value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_MAXMSGSIZE:
    {
      int64_t value;
      value_len = sizeof(int64_t);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_SUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_UNSUBSCRIBE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_TYPE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TYPE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVMORE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVMORE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_EVENTS:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_EVENTS value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_SNDTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_RCVTIMEO:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_IPV4ONLY:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_IPV4ONLY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_LAST_ENDPOINT:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_LAST_ENDPOINT value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len - 1, CopyString);
    }
  	
    case ZMQ_TCP_KEEPALIVE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_TCP_KEEPALIVE_IDLE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_TCP_KEEPALIVE_CNT:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_TCP_KEEPALIVE_INTVL:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_TCP_ACCEPT_FILTER:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_TCP_ACCEPT_FILTER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  	
    case ZMQ_DELAY_ATTACH_ON_CONNECT:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_DELAY_ATTACH_ON_CONNECT value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_XPUB_VERBOSE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_XPUB_VERBOSE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_ROUTER_MANDATORY:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Getting ZMQ::SOCKOPT_ROUTER_MANDATORY is not supported", PHP_ZMQ_INTERNAL_ERROR);
  	
    case ZMQ_ROUTER_RAW:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_ROUTER_RAW value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_IPV6:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_IPV6 value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_PLAIN_SERVER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_PLAIN_SERVER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_PLAIN_USERNAME:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_PLAIN_USERNAME value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  
    case ZMQ_PLAIN_PASSWORD:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_PLAIN_PASSWORD value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  	
    case ZMQ_CURVE_SERVER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_CURVE_SERVER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_CURVE_PUBLICKEY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_CURVE_PUBLICKEY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  
    case ZMQ_CURVE_SECRETKEY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_CURVE_SECRETKEY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  
    case ZMQ_CURVE_SERVERKEY:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_CURVE_SERVERKEY value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  	
    case ZMQ_PROBE_ROUTER:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_PROBE_ROUTER value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_REQ_CORRELATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_REQ_CORRELATE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_REQ_RELAXED:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_REQ_RELAXED value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  	
    case ZMQ_CONFLATE:
    {
      int value;
      value_len = sizeof(int);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_CONFLATE value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  
    case ZMQ_ZAP_DOMAIN:
    {
      char value[255];

      value_len = 255;
      if (zmq_getsockopt(intern->socket->z_socket, key, &value, &value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_ZAP_DOMAIN value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  

    case ZMQ_FD:
    {
      php_stream *stm = php_zmq_create_zmq_fd(getThis());
      if (stm) {
        php_stream_to_zval(stm, return_value);
        return;
      }
      return false;
    }
    break;

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
}

  

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
  Set a socket option
*/
ZMQSocketObject* HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant& pz_value) {
  auto intern = Native::data<ZMQSocketObject>(this_);
  int status;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  

    case ZMQ_SNDHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDHWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVHWM:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVHWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_AFFINITY:
    {
      
      int64_t iVal = pz_value.toInt64();
      uint64_t value = (uint64_t)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_AFFINITY value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_AFFINITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_IDENTITY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_IDENTITY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RATE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECOVERY_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SNDBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVBUF:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVBUF option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_LINGER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_LINGER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RECONNECT_IVL_MAX:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_BACKLOG:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_BACKLOG option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_MAXMSGSIZE:
    {
      int64_t value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_SUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_UNSUBSCRIBE:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    case ZMQ_TYPE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  
    case ZMQ_RCVMORE:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
  

    case ZMQ_SNDTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_RCVTIMEO:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_IPV4ONLY:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_IPV4ONLY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    case ZMQ_LAST_ENDPOINT:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Setting ZMQ::SOCKOPT_LAST_ENDPOINT is not supported", PHP_ZMQ_INTERNAL_ERROR);
  

    case ZMQ_TCP_KEEPALIVE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_TCP_KEEPALIVE_IDLE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_TCP_KEEPALIVE_CNT:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_TCP_KEEPALIVE_INTVL:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_TCP_ACCEPT_FILTER:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_TCP_ACCEPT_FILTER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_DELAY_ATTACH_ON_CONNECT:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_DELAY_ATTACH_ON_CONNECT option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_XPUB_VERBOSE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_XPUB_VERBOSE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_ROUTER_MANDATORY:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_ROUTER_MANDATORY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_ROUTER_RAW:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_ROUTER_RAW option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_IPV6:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_IPV6 option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_PLAIN_SERVER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_PLAIN_SERVER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_PLAIN_USERNAME:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_PLAIN_USERNAME option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_PLAIN_PASSWORD:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_PLAIN_PASSWORD option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_CURVE_SERVER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_CURVE_SERVER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_CURVE_PUBLICKEY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_CURVE_PUBLICKEY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_CURVE_SECRETKEY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_CURVE_SECRETKEY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_CURVE_SERVERKEY:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_CURVE_SERVERKEY option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_PROBE_ROUTER:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_PROBE_ROUTER option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_REQ_CORRELATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_REQ_CORRELATE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_REQ_RELAXED:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_REQ_RELAXED option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_CONFLATE:
    {
      int value = pz_value.toInt32();
        
      status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_CONFLATE option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  

    case ZMQ_ZAP_DOMAIN:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_ZAP_DOMAIN option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  
    
    case ZMQ_HWM:
    {
      int64_t iVal = pz_value.toInt64();
      int value = (int)iVal;

      if (iVal < 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
      
      status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

      if (status == 0) {
        status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
      }
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }
  

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return intern;
}

  

void ZMQExtension::registerSockoptConstants()
{
  static const StaticString s_ZMQ("ZMQ");
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  static const StaticString s_##const_name("const_name"); \
  Native::registerClassConstant<KindOfInt64>(s_ZMQ.get(), s_##const_name.get(), value);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_HWM, ZMQ_HWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDHWM, ZMQ_SNDHWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVHWM, ZMQ_RCVHWM);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_AFFINITY, ZMQ_AFFINITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_IDENTITY, ZMQ_IDENTITY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RATE, ZMQ_RATE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECOVERY_IVL, ZMQ_RECOVERY_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDBUF, ZMQ_SNDBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVBUF, ZMQ_RCVBUF);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_LINGER, ZMQ_LINGER);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL, ZMQ_RECONNECT_IVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RECONNECT_IVL_MAX, ZMQ_RECONNECT_IVL_MAX);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_BACKLOG, ZMQ_BACKLOG);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_MAXMSGSIZE, ZMQ_MAXMSGSIZE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SUBSCRIBE, ZMQ_SUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_UNSUBSCRIBE, ZMQ_UNSUBSCRIBE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TYPE, ZMQ_TYPE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVMORE, ZMQ_RCVMORE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_FD, ZMQ_FD);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_EVENTS, ZMQ_EVENTS);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_SNDTIMEO, ZMQ_SNDTIMEO);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_RCVTIMEO, ZMQ_RCVTIMEO);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_IPV4ONLY, ZMQ_IPV4ONLY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_LAST_ENDPOINT, ZMQ_LAST_ENDPOINT);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_KEEPALIVE, ZMQ_TCP_KEEPALIVE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_KEEPALIVE_IDLE, ZMQ_TCP_KEEPALIVE_IDLE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_KEEPALIVE_CNT, ZMQ_TCP_KEEPALIVE_CNT);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_KEEPALIVE_INTVL, ZMQ_TCP_KEEPALIVE_INTVL);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_TCP_ACCEPT_FILTER, ZMQ_TCP_ACCEPT_FILTER);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_DELAY_ATTACH_ON_CONNECT, ZMQ_DELAY_ATTACH_ON_CONNECT);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_XPUB_VERBOSE, ZMQ_XPUB_VERBOSE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_ROUTER_MANDATORY, ZMQ_ROUTER_MANDATORY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_ROUTER_RAW, ZMQ_ROUTER_RAW);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_IPV6, ZMQ_IPV6);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_PLAIN_SERVER, ZMQ_PLAIN_SERVER);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_PLAIN_USERNAME, ZMQ_PLAIN_USERNAME);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_PLAIN_PASSWORD, ZMQ_PLAIN_PASSWORD);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_CURVE_SERVER, ZMQ_CURVE_SERVER);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_CURVE_PUBLICKEY, ZMQ_CURVE_PUBLICKEY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_CURVE_SECRETKEY, ZMQ_CURVE_SECRETKEY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_CURVE_SERVERKEY, ZMQ_CURVE_SERVERKEY);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_PROBE_ROUTER, ZMQ_PROBE_ROUTER);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_REQ_CORRELATE, ZMQ_REQ_CORRELATE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_REQ_RELAXED, ZMQ_REQ_RELAXED);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_CONFLATE, ZMQ_CONFLATE);
      
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_ZAP_DOMAIN, ZMQ_ZAP_DOMAIN);
      
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      
#endif

}}
  