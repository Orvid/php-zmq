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

#define HAVE_LIBCZMQ_2 1

#ifdef HAVE_LIBCZMQ_2
#include <czmq.h>
#endif

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
  static void initializeClock();
  static uint64_t clock();
  static String getLibVersion();
};

struct ZMQContextData {
  void *z_ctx;
  int io_threads;
  bool is_persistent;
  bool is_global;
  int pid;

  ~ZMQContextData() {
    if (!is_global && pid == getpid()) {
      zmq_term(z_ctx);
    }
  }

  static ZMQContextData* get(int64_t io_threads,
                             bool is_persistent,
                             bool is_global);

private:
  ZMQContextData(int ioThreads, bool isPersistent, bool isGlobal);
};

struct ZMQContext {
  ZMQContextData* context;

  ~ZMQContext() {
    if (context && !context->is_persistent) {
      delete context;
    }
  }
};

struct ZMQSocketData {
  void* z_socket;
  ZMQContextData* ctx;
  hphp_hash_set<String> connect;
  hphp_hash_set<String> bind;
  bool is_persistent;
  /* Who created me */
  int pid;

  ~ZMQSocketData() {
    if (pid == getpid()) {
      zmq_close(z_socket);
    }
  }

  static ZMQSocketData* get(ZMQContextData* ctx, int64_t type, const Variant& persistentId, bool& isNew);
  static void set(ZMQSocketData* sock, int64_t type, const Variant& persistentId);

private:
  ZMQSocketData(ZMQContextData* ctx, int64_t type, bool isPersistent);
};

struct ZMQSocket {
  ZMQSocketData* socket;
  String persistent_id;
  Object context_obj;

  ~ZMQSocket() {
    if (socket && !socket->is_persistent) {
      delete socket;
    }
  }

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

  ZMQPollItem(int pEvents, Variant pEntry, String pKey, int pfd)
    : events(pEvents), entry(pEntry), key(pKey), fd(pfd) {
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

  void clear();
  void assign(const Variant& cb, int64_t time, const Variant& ud);
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

#ifdef HAVE_LIBCZMQ_2
struct ZMQCert {
  zcert_t* zcert;

  ZMQCert() = default;

  ~ZMQCert() {
    if (zcert) {
      zcert_destroy(&zcert);
    }
  }

  ZMQCert* operator =(const ZMQCert& other) {
    zcert = zcert_dup(other.zcert);
    return this;
  }
};

#define PHP_ZMQ_AUTH_TYPE_PLAIN 0
#define PHP_ZMQ_AUTH_TYPE_CURVE 1
enum class ZMQAuthType : int64_t {
  Plain = 0,
  Curve = 1,
};

struct ZMQAuth {
  zctx_t* shadow_context;
  zauth_t* zauth;

  ~ZMQAuth() {
    if (shadow_context) {
      zctx_destroy(&shadow_context);
    }
    if (zauth) {
      zauth_destroy(&zauth);
    }
  }
};
#endif

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
