<?hh

class ZMQ {
  const int CTXOPT_MAX_SOCKETS;
  const int CTXOPT_MAX_SOCKETS_DEFAULT;

  const int DEVICE_FORWARDER;
  const int DEVICE_QUEUE;
  const int DEVICE_STREAMER;

  const int ERR_INTERNAL;
  const int ERR_EAGAIN;
  const int ERR_ENOTSUP;
  const int ERR_EFSM;
  const int ERR_ETERM;

  const string LIBZMQ_VER;

  const int MODE_SNDMORE;
  const int MODE_NOBLOCK;
  const int MODE_DONTWAIT;

  const int POLL_IN;
  const int POLL_OUT;

  const int SOCKET_PAIR;
  const int SOCKET_PUB;
  const int SOCKET_SUB;
  const int SOCKET_XSUB;
  const int SOCKET_XPUB;
  const int SOCKET_REQ;
  const int SOCKET_REP;
  const int SOCKET_XREQ;
  const int SOCKET_XREP;
  const int SOCKET_PUSH;
  const int SOCKET_PULL;
  const int SOCKET_DEALER;
  const int SOCKET_ROUTER;
  const int SOCKET_STREAM;
  const int SOCKET_UPSTREAM;
  const int SOCKET_DOWNSTREAM;

  const int SOCKOPT_AFFINITY;
  const int SOCKOPT_BACKLOG;
  const int SOCKOPT_CONFLATE;
  const int SOCKOPT_CURVE_PUBLICKEY;
  const int SOCKOPT_CURVE_SECRETKEY;
  const int SOCKOPT_CURVE_SERVER;
  const int SOCKOPT_CURVE_SERVERKEY;
  const int SOCKOPT_DELAY_ATTACH_ON_CONNECT;
  const int SOCKOPT_EVENTS;
  const int SOCKOPT_FD;
  const int SOCKOPT_IDENTITY;
  const int SOCKOPT_IPV4ONLY;
  const int SOCKOPT_IPV6;
  const int SOCKOPT_LAST_ENDPOINT;
  const int SOCKOPT_LINGER;
  const int SOCKOPT_MAXMSGSIZE;
  const int SOCKOPT_PLAIN_PASSWORD;
  const int SOCKOPT_PLAIN_SERVER;
  const int SOCKOPT_PLAIN_USERNAME;
  const int SOCKOPT_PROBE_ROUTER;
  const int SOCKOPT_RATE;
  const int SOCKOPT_RCVBUF;
  const int SOCKOPT_RCVHWM;
  const int SOCKOPT_RCVMORE;
  const int SOCKOPT_RCVTIMEO;
  const int SOCKOPT_RECONNECT_IVL;
  const int SOCKOPT_RECONNECT_IVL_MAX;
  const int SOCKOPT_RECOVERY_IVL;
  const int SOCKOPT_REQ_CORRELATE;
  const int SOCKOPT_REQ_RELAXED;
  const int SOCKOPT_ROUTER_MANDATORY;
  const int SOCKOPT_ROUTER_RAW;
  const int SOCKOPT_SNDBUF;
  const int SOCKOPT_SNDHWM;
  const int SOCKOPT_SNDTIMEO;
  const int SOCKOPT_SUBSCRIBE;
  const int SOCKOPT_TCP_ACCEPT_FILTER;
  const int SOCKOPT_TCP_KEEPALIVE;
  const int SOCKOPT_TCP_KEEPALIVE_CNT;
  const int SOCKOPT_TCP_KEEPALIVE_IDLE;
  const int SOCKOPT_TCP_KEEPALIVE_INTVL;
  const int SOCKOPT_TYPE;
  const int SOCKOPT_UNSUBSCRIBE;
  const int SOCKOPT_XPUB_VERBOSE;
  const int SOCKOPT_ZAP_DOMAIN;

  public static function clock(): int;
}

class ZMQContext {
  public function __construct(int $io_threads = 1, bool $is_persistent = true): void;
  public static function acquire() : ZMQContext;
  public function getSocket(int $type, ?string $persistent_id = null, ?mixed $on_new_socket = null): ZMQSocket;
  public function isPersistent() : bool;
  public function setOpt(int $option, int $value): void;
  public function getOpt(int $option): int;
}

class ZMQSocket {
  public function __construct(ZMQContext $context, int $type, ?string $persistent_id = null, ?mixed $on_new_socket = null): void;
  public function send(string $message, int $flags = 0): mixed;
  public function sendMulti(array $message, int $flags = 0): mixed;
  public function recv(int $flags = 0): mixed;
  public function recvMulti(int $flags = 0): mixed;
  public function getPersistentId(): ?string;
  public function bind(string $dsn, bool $force = false): ZMQSocket;
  public function connect(string $dsn, bool $force = false): ZMQSocket;
  public function unbind(string $dsn): ZMQSocket;
  public function disconnect(string $dsn): ZMQSocket;
  public function setSockOpt(int $key, mixed $value): ZMQSocket;
  public function getSockOpt(int $key): mixed;
  public function getEndpoints(): array;
  public function getSocketType(): int;
  public function isPersistent(): bool;
}

class ZMQPoll {
  public function add(mixed $object, int $type): string;
  public function remove(mixed $item): bool;
  public function poll(mixed& $readable, mixed& $writable, int $timeout = -1): int;
  public function count(): int;
  public function clear(): ZMQPoll;
  public function getLastErrors(): array;
}

class ZMQDevice {
  public function __construct(ZMQSocket $frontend, ZMQSocket $backend, ?ZMQSocket $capture = null): void;
  public function run(): void;
  public function getIdleTimeout(): int;
  public function setIdleTimeout(int $timeout): ZMQDevice;
  public function getTimerTimeout(): int;
  public function setTimerTimeout(int $timeout): ZMQDevice;
  public function setIdleCallback(mixed $idle_callback, int $timeout, ?mixed $user_data = null): ZMQDevice;
  public function setTimerCallback(mixed $idle_callback, int $timeout, ?mixed $user_data = null): ZMQDevice;
}

class ZMQException extends Exception { }
final class ZMQContextException extends ZMQException { }
final class ZMQSocketException extends ZMQException { }
final class ZMQPollException extends ZMQException { }
final class ZMQDeviceException extends ZMQException { }
