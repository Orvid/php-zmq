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
#ifndef incl_HPHP_EXT_ZMQ_H_
#define incl_HPHP_EXT_ZMQ_H_

#include "hphp/runtime/ext/extension.h"

namespace HPHP { namespace zmq {

#define PHP_ZMQ_VERSION "1.1.2"
class ZMQExtension final : public Extension {
public:
  ZMQExtension() : Extension("zmq", PHP_ZMQ_VERSION) {}
  void moduleInit() override;
  void moduleInfo(Array &info) override;

private:
  void registerSockoptConstants();
  void initializeExceptionReferences();
};

}}

#endif
