<xsl:stylesheet
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  version="1.0">
  <xsl:output indent="no" method="text"/>
  <xsl:template match="/">
    <xsl:call-template name="file-header"/>
    
    <xsl:for-each select="/options/version">
#if <xsl:value-of select="@comparison" />

      <!-- start ZMQSocket::getSockOpt -->
      <xsl:call-template name="getsockopt-header"/>
      <xsl:for-each select="option">
        
        <xsl:variable name="raw-name">
          <xsl:call-template name="convert-to-uppercase">
            <xsl:with-param name="input-string" select="@name"/>
          </xsl:call-template>
        </xsl:variable>
        <xsl:variable name="const-name" select="concat('ZMQ_', $raw-name)"/>

        <xsl:variable name="max-length">
          <xsl:choose>
              <xsl:when test="@max-length">
              <xsl:value-of select="@max-length"/>
            </xsl:when>
              <xsl:otherwise>255</xsl:otherwise>
          </xsl:choose>
        </xsl:variable>

        <xsl:if test="@name != 'fd'">	
          <xsl:choose>
            <xsl:when test="@mode = 'rw' or @mode = 'r'">
              <xsl:call-template name="get-option">
                <xsl:with-param name="const-name" select="$const-name"/>
                <xsl:with-param name="raw-name" select="$raw-name"/>
                <xsl:with-param name="type" select="@type"/>
                <xsl:with-param name="max-length" select="$max-length"/>
              </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
              <xsl:call-template name="unsupported-operation">
                <xsl:with-param name="operation" select="'Getting'"/>
                <xsl:with-param name="const-name" select="$const-name"/>
                <xsl:with-param name="raw-name" select="$raw-name"/>
              </xsl:call-template>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:if>
      </xsl:for-each>
      <xsl:call-template name="getsockopt-footer" />
      <!-- end ZMQSocket::getSockOpt -->

      <!-- start ZMQSocket::setSockOpt -->
      <xsl:call-template name="setsockopt-header"/>

      <xsl:for-each select="option">
        <xsl:variable name="raw-name">
          <xsl:call-template name="convert-to-uppercase">
            <xsl:with-param name="input-string" select="@name"/>
          </xsl:call-template>
        </xsl:variable>
        <xsl:variable name="const-name" select="concat('ZMQ_', $raw-name)"/>
        <xsl:if test="@name != 'fd' and @name != 'events'">
          <xsl:choose>
            <xsl:when test="@mode = 'rw' or @mode = 'w'">
              <xsl:call-template name="set-option">
                <xsl:with-param name="const-name" select="$const-name"/>
                <xsl:with-param name="type" select="@type"/>
                <xsl:with-param name="raw-name" select="$raw-name"/>
              </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
              <xsl:call-template name="unsupported-operation">
                <xsl:with-param name="operation" select="'Setting'"/>
                <xsl:with-param name="const-name" select="$const-name"/>
                <xsl:with-param name="raw-name" select="$raw-name"/>
              </xsl:call-template>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:if>
      </xsl:for-each>
      
      <xsl:if test="@major = 3 or @major = 4">
        <xsl:call-template name="set-hwm-bwc"/>
      </xsl:if>
  
      <xsl:call-template name="setsockopt-footer" />

void ZMQExtension::registerSockoptConstants()
{
  static const StaticString s_ZMQ("ZMQ");
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
  static const StaticString s_##const_name("const_name"); \
  Native::registerClassConstant&lt;KindOfInt64&gt;(s_ZMQ.get(), s_##const_name.get(), value);
      <xsl:if test="@major = 3 or @major = 4">
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_HWM, ZMQ_HWM);
      </xsl:if>
      <xsl:for-each select="option">
        <xsl:variable name="raw-name">
          <xsl:call-template name="convert-to-uppercase">
            <xsl:with-param name="input-string" select="@name"/>
          </xsl:call-template>
        </xsl:variable>
  PHP_ZMQ_REGISTER_SOCKOPT(SOCKOPT_<xsl:value-of select="$raw-name"/>, ZMQ_<xsl:value-of select="$raw-name"/>);
      </xsl:for-each>
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
      <!-- end ZMQSocket::setSockOpt -->
#endif
</xsl:for-each>
    <xsl:call-template name="file-footer"/>
  </xsl:template>
  
  
  <xsl:template name="getsockopt-header">

/*
  Get a socket option
*/
Variant HHVM_METHOD(ZMQSocket, getSockOpt, int key) {
  auto intern = Native::data&lt;ZMQSocket&gt;(this_);
  size_t value_len;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  </xsl:template>
  <xsl:template name="getsockopt-footer">

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

  </xsl:template>

  <xsl:template name="unsupported-operation">
    <xsl:param name="operation"/>
    <xsl:param name="const-name"/>
    <xsl:param name="raw-name"/>
    case <xsl:value-of select="$const-name"/>:
      throwExceptionClass(s_ZMQSocketExceptionClass, "<xsl:value-of select="$operation"/> ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> is not supported", PHP_ZMQ_INTERNAL_ERROR);
  </xsl:template>

  <xsl:template name="get-numeric-option">
    <xsl:param name="const-name"/>
    <xsl:param name="raw-name"/>
    <xsl:param name="type"/>	
    case <xsl:value-of select="$const-name"/>:
    {
      <xsl:value-of select="$type"/> value;
      value_len = sizeof(<xsl:value-of select="$type"/>);
      
      if (zmq_getsockopt(intern->socket->z_socket, key, &amp;value, &amp;value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> value: {}", zmq_strerror(errno)).str(), errno);
      }
      return value;
    }
  </xsl:template>

  <xsl:template name="get-blob-option">
    <xsl:param name="const-name"/>
    <xsl:param name="raw-name"/>
    <xsl:param name="max-length"/>
    case <xsl:value-of select="$const-name"/>:
    {
      char value[<xsl:value-of select="$max-length"/>];

      value_len = <xsl:value-of select="$max-length"/>;
      if (zmq_getsockopt(intern->socket->z_socket, key, &amp;value, &amp;value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len, CopyString);
    }
  </xsl:template>

  <xsl:template name="get-string-option">
    <xsl:param name="const-name"/>
    <xsl:param name="raw-name"/>
    <xsl:param name="max-length"/>
    case <xsl:value-of select="$const-name"/>:
    {
      char value[<xsl:value-of select="$max-length"/>];

      value_len = <xsl:value-of select="$max-length"/>;
      if (zmq_getsockopt(intern->socket->z_socket, key, &amp;value, &amp;value_len) != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to get the option ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> value: {}", zmq_strerror(errno)).str(), errno);
      }
      return String(value, value_len - 1, CopyString);
    }
  </xsl:template>
  
  <xsl:template name="get-option">
    <xsl:param name="const-name"/>
    <xsl:param name="raw-name"/>
    <xsl:param name="type"/>
    <xsl:param name="max-length" select="'xyz'"/>
    
    <xsl:choose>
      <xsl:when test="$type = 'blob'">
        <xsl:call-template name="get-blob-option">
          <xsl:with-param name="const-name" select="$const-name"/>
          <xsl:with-param name="raw-name" select="$raw-name"/>
          <xsl:with-param name="max-length" select="$max-length"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$type = 'string'">
        <xsl:call-template name="get-string-option">
          <xsl:with-param name="const-name" select="$const-name"/>
          <xsl:with-param name="raw-name" select="$raw-name"/>
          <xsl:with-param name="max-length" select="$max-length"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:call-template name="get-numeric-option">
          <xsl:with-param name="const-name" select="$const-name"/>
          <xsl:with-param name="type" select="$type"/>
          <xsl:with-param name="raw-name" select="$raw-name"/>
        </xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
  <xsl:template name="setsockopt-header">

/*
  Set a socket option
*/
Object HHVM_METHOD(ZMQSocket, setSockOpt, int key, const Variant&amp; pz_value) {
  auto intern = Native::data&lt;ZMQSocket&gt;(this_);
  int status;

  if (!intern->socket) {
    throwExceptionClass(s_ZMQSocketExceptionClass, "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR);
  }

  switch (key) {

  </xsl:template>

  <xsl:template name="setsockopt-footer">

    default:
      throwExceptionClass(s_ZMQSocketExceptionClass, "Unknown option key", PHP_ZMQ_INTERNAL_ERROR);
  }
  return intern;
}

  </xsl:template>
  
  <xsl:template name="set-string-option">
    <xsl:param name="const-name"/>
    <xsl:param name="raw-name"/>

    case <xsl:value-of select="$const-name"/>:
    {
      auto strVal = pz_value.toStrNR();
      status = zmq_setsockopt(intern->socket->z_socket, key, strVal.data(), strVal.size());

      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  </xsl:template>
  
  <xsl:template name="set-numeric-option">
    <xsl:param name="const-name"/>
    <xsl:param name="raw-name"/>
    <xsl:param name="type"/>

    case <xsl:value-of select="$const-name"/>:
    {
      <xsl:choose>
        <xsl:when test="$type = 'uint64_t'">
      int64_t iVal = pz_value.toInt64();
      <xsl:value-of select="$type"/> value = (uint64_t)iVal;

      if (iVal &lt; 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
        </xsl:when>
        <xsl:otherwise>
      <xsl:value-of select="$type"/> value = pz_value.toInt32();
        </xsl:otherwise>
      </xsl:choose>
      status = zmq_setsockopt(intern->socket->z_socket, key, &amp;value, sizeof(<xsl:value-of select="$type"/>));
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }

  </xsl:template>

  <xsl:template name="set-option">
    <xsl:param name="const-name"/>
    <xsl:param name="raw-name"/>
    <xsl:param name="type"/>
    
    <xsl:choose>
      <xsl:when test="$type = 'blob'">
        <xsl:call-template name="set-string-option">
          <xsl:with-param name="const-name" select="$const-name"/>
          <xsl:with-param name="raw-name" select="$raw-name"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:call-template name="set-numeric-option">
          <xsl:with-param name="const-name" select="$const-name"/>
          <xsl:with-param name="type" select="$type"/>
          <xsl:with-param name="raw-name" select="$raw-name"/>
        </xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
  <xsl:template name="set-hwm-bwc">
    
    case ZMQ_HWM:
    {
      int64_t iVal = pz_value.toInt64();
      int value = (int)iVal;

      if (iVal &lt; 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, "The option must be zero or larger", PHP_ZMQ_INTERNAL_ERROR);
      }
      
      status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &amp;value, sizeof(int));

      if (status == 0) {
        status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &amp;value, sizeof(int));
      }
      
      if (status != 0) {
        throwExceptionClass(s_ZMQSocketExceptionClass, folly::format("Failed to set socket ZMQ::SOCKOPT_HWM option: {}", zmq_strerror(errno)).str(), errno);
      }
      break;
    }
  </xsl:template>
  
  <xsl:template name="convert-to-uppercase">
    <xsl:param name="input-string"/>
  
    <xsl:variable name="lower" select="'abcdefghijklmnopqrstuvwxyz'" />
    <xsl:variable name="upper" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'" />

      <xsl:value-of select="translate($input-string, $lower, $upper)" />
  </xsl:template>
  
  <xsl:template name="file-header">
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

#include &lt;folly/Format.h&gt;

namespace HPHP { namespace zmq {
  </xsl:template>
  
  <xsl:template name="file-footer">
}}
  </xsl:template>
  
</xsl:stylesheet>
