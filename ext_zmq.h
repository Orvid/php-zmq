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
#include "hphp/util/hash.h"
#include <zmq.h>

// TODO: This is a bad hack, and should at the very least be
// using the existing hashing functionality for strings.
#include <xstddef>
namespace std {
template <>
struct hash<HPHP::String> {
  std::size_t operator()(const HPHP::String& k) const {
    return std::hash<std::string>()(k.toCppString());
  }
};
}

namespace HPHP { namespace zmq {

struct ZMQ {
  static uint64_t clock() {
    return 0;
  }
};

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
  Object context_obj;

  bool send(const String& message_param, int64_t flags);
  bool recv(int64_t flags, String& msg);
};

struct ZMQPollItem {
  int events;
  Variant entry;
  String key;

  /* convenience pointer containing fd or socket */
  void* socket;
  int fd;

  ZMQPollItem(int pEvents, Variant pEntry, String pKey, void* pSocket)
    : events(pEvents), entry(pEntry), key(pKey), socket(pSocket) {
  }
};

#define PHP_ZMQ_POLLSET_ERR_NO_STREAM    -1
#define PHP_ZMQ_POLLSET_ERR_CANNOT_CAST  -2
#define PHP_ZMQ_POLLSET_ERR_CAST_FAILED  -3
#define PHP_ZMQ_POLLSET_ERR_NO_INIT      -4
#define PHP_ZMQ_POLLSET_ERR_NO_POLL      -5
#define PHP_ZMQ_POLLSET_ERR_KEY_FAIL     -6
#define PHP_ZMQ_POLLSET_ERR_INVALID_TYPE -7
struct ZMQPollData {
  std::vector<ZMQPollItem> php_items;
  std::vector<zmq_pollitem_t> items;
  /* Errors in the last poll */
  Array errors{ Array::Create() };

  int add(const Variant& obj, int64_t events);
  bool getKey(int pos, String& key);
  bool erase(const Variant& entry);
  bool eraseByKey(const String& key);
  void eraseAll();
  int poll(int64_t timeout, VRefParam readable, VRefParam writable);

private:
  static String createKey(const Variant& obj);
};

struct ZMQPoll {
  ZMQPollData set;
};

struct ZMQDeviceCallback {
  bool initialized{ false };
  long timeout;
  Variant callback;
  Variant user_data;
  uint64_t scheduled_at;

  bool invoke(uint64_t currentTime);
};

struct ZMQDevice {
  ZMQDeviceCallback idle_cb;
  ZMQDeviceCallback timer_cb;

  Object front;
  Object back;
  Object capture;

  bool run();

private:
  int calculateTimeout();
  static bool handleSocketRecieved(void* sockA, void* sockB, void* captureSock, zmq_msg_t* msg);
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
