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

struct ZMQContextData {
  /* zmq context */
  void *z_ctx;
  /* Amount of io-threads */
  int io_threads;
  /* Is this a persistent context */
  bool is_persistent;
  /* Should this context live to end of request */
  bool is_global;
  /* Who created me */
  int pid;

  ZMQContextData(int ioThreads, bool isPersistent, bool isGlobal) :
    io_threads(ioThreads),
    is_persistent(isPersistent),
    is_global(isGlobal),
    pid(getpid()) {
  }
};

struct ZMQContext {
  ZMQContextData* context;

  static ZMQContextData* createData(int64_t io_threads,
                                    bool is_persistent,
                                    bool is_global);
};

struct ZMQSocketData {
  void* z_socket;
  ZMQContextData* ctx;
  hphp_hash_set<String> connect;
  hphp_hash_set<String> bind;
  bool is_persistent;
  /* Who created me */
  int pid;
};

struct ZMQSocket {
  ZMQSocketData* socket;
  /* options for the context */
  char* persistent_id;
  /* zval of the context */
  //zval* context_obj;

  bool send(const String& message_param, int64_t flags);
  bool recv(int64_t flags, String& msg);
};


class ZMQExtension final : public Extension {
public:
  ZMQExtension() : Extension("zmq") {}
  void moduleInit() override;

private:
  void registerSockoptConstants();
  void initializeExceptionReferences();
};

}}

#endif
