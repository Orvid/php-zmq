<?hh

/**
 * @EXTRA - None of these exceptions are defined in the original.
 */
class ZMQException extends Exception { }
final class ZMQContextException extends ZMQException { }
final class ZMQSocketException extends ZMQException { }
final class ZMQPollException extends ZMQException { }
final class ZMQDeviceException extends ZMQException { }

/**
 * @EXTRA - Everything in this is extra.
 */
class ZMQ {
  <<__Native>>
  public static function clock(): int;
}

<<__NativeData("ZMQContext")>>
class ZMQContext {
  /**
   * Build a new ZMQContext. Persistent context is required for building
   * persistent sockets.
   *
   *
   * @param integer $io_threads     Number of io threads
   * @param boolean $is_persistent  Whether the context is persistent
   *
   * @return void
   */
  <<__Native>>
  public function __construct(int $io_threads = 1, bool $is_persistent = true): void;

  /**
   * Acquires a handle to the request global context.
   * @EXTRA
   */
  <<__Native>>
  public static function acquire() : ZMQContext;

  /**
   * Construct a new ZMQ object. The extending class must call this method.
   * The type is one of the ZMQ::SOCKET_* constants.
   * Persistent id allows reusing the socket over multiple requests.
   * If persistent_id parameter is specific the type parameter is ignored and the
   * socket is of type that it was initially created with. Persistent context must
   * be enabled for persistent_id to work. Setting incorrect socket type might
   * cause failure later in connect/bind/setSockOpt.
   *
   * @param integer $type              The type of the socket
   * @param string  $persistent_id     The persistent id. Can be used to create
   *                                   persistent connections
   * @param function   $on_new_socket     Called when a new socket is created
   * @throws ZMQException
   * @return ZMQSocket
   */
  <<__Native>>
  public function getSocket(int $type, ?string $persistent_id = null, ?mixed $on_new_socket = null): ZMQSocket;

  /**
   * Whether the context is persistent
   *
   * @return boolean
   */
  <<__Native>>
  public function isPersistent() : bool;

  /**
   * Set a context option
   *
   * @param int $option
   * @param int $value
   * @EXTRA
   */
  <<__Native>>
  public function setOpt(int $option, int $value): void;

  /**
   * Get a context option
   *
   * @param int $option
   * @EXTRA
   */
  <<__Native>>
  public function getOpt(int $option): int;
}

<<__NativeData("ZMQSocket")>>
class ZMQSocket {
  /**
   * Construct a new ZMQ object. The extending class must call this method.
   * The type is one of the ZMQ::SOCKET_* constants.
   * Persistent id allows reusing the socket over multiple requests.
   * If persistent_id parameter is specific the type parameter is ignored and the
   * socket is of type that it was initially created with. Persistent context must
   * be enabled for persistent_id to work. Setting incorrect socket type might
   * cause failure later in connect/bind/setSockOpt.
   *
   * @param ZMQContext $context           ZMQContext to build this object
   * @param integer    $type              The type of the socket
   * @param string     $persistent_id     The persistent id. Can be used to create
   *                                      persistent connections
   * @param function   $on_new_socket     Called when a new socket is created
   * @throws ZMQException
   * @return void
   */
  <<__Native>>
  public function __construct(ZMQContext $context, int $type, ?string $persistent_id = null, ?mixed $on_new_socket = null): void;

  /**
   * Sends a message to the queue.
   *
   * @param string  $message  The message to send
   * @param integer $flags    self::MODE_NOBLOCK or 0
   * @throws ZMQException if sending message fails
   *
   * @return ZMQSocket|false
   */
  <<__Native>>
  public function send(string $message, int $flags = 0): mixed;

  /**
   * Send a multipart message. Return true if message was sent and false on EAGAIN
   *
   * @param array $messages
   * @param integer $flags
   * @return ZMQSocket|false
   * @EXTRA
   */
  <<__Native>>
  public function sendMulti(array $message, int $flags = 0): mixed;

  /**
   * Receives a message from the queue.
   *
   * @param integer $flags self::MODE_NOBLOCK or 0
   * @throws ZMQException if receiving fails.
   *
   * @return string|false
   */
  <<__Native>>
  public function recv(int $flags = 0): mixed;

  /**
   * Receive an array of message parts
   *
   * @return array<string>|false
   * @EXTRA
   */
  <<__Native>>
  public function recvMulti(int $flags = 0): mixed;

  /**
   * Returns the persistent id of the object
   *
   * @return string|null
   * @EXTRA
   */
  <<__Native>>
  public function getPersistentId(): ?string;

  /**
   *
   * Binds the socket to an end-point. For more information about the dsn see
   * http://api.zeromq.org/zmq_connect.html. By default the method does not
   * try to bind if it has been already bound to the address specified by $dsn.
   *
   * @param string  $dsn   The bind dsn
   * @param boolean $force Tries to bind to end-point even if the object is already bound to the $dsn
   *
   * @throws ZMQException if binding fails
   * @return ZMQ
   */
  <<__Native>>
  public function bind(string $dsn, bool $force = false): ZMQSocket;

  /**
   * Connect the socket to a remote endpoint. For more information about the dsn
   * see http://api.zeromq.org/zmq_connect.html. By default the method does not
   * try to connect if it has been already connected to the address specified by $dsn.
   *
   * @param string  $dsn   The connect dsn
   * @param boolean $force Tries to connect to end-point even if the object is already connected to the $dsn
   *
   * @throws ZMQException If connection fails
   * @return ZMQ
   */
  <<__Native>>
  public function connect(string $dsn, bool $force = false): ZMQSocket;

  /**
   * Unbind the socket from an endpoint
   * @EXTRA
   */
  <<__Native>>
  public function unbind(string $dsn): ZMQSocket;

  /**
   * Disconnect the socket from an endpoint
   * @EXTRA
   */
  <<__Native>>
  public function disconnect(string $dsn): ZMQSocket;

  /**
   * Sets a socket option. For more information about socket options see
   * http://api.zeromq.org/zmq_setsockopt.html
   *
   * @param integer $key   The option key
   * @param mixed   $value The option value
   *
   * @throws ZMQException
   * @return ZMQ
   */
  <<__Native>>
  public function setSockOpt(int $key, mixed $value): ZMQSocket;

  /**
   * Gets a socket option. This method is available if ZMQ extension
   * has been compiled against ZMQ version 2.0.7 or higher
   *
   * @since 0MQ 2.0.7
   * @param integer $key The option key
   *
   * @throws ZMQException
   * @return mixed
   */
  <<__Native>>
  public function getSockOpt(int $key): mixed;

  /**
   * Get endpoints where the socket is connected to. The return array
   * contains two sub-arrays: 'connect' and 'bind'
   *
   * @throws ZMQException
   * @return array
   */
  <<__Native>>
  public function getEndpoints(): array;

  /**
   * Return the socket type. Returns one of ZMQ::SOCKET_* constants
   *
   * @throws ZMQException
   * @return integer
   */
  <<__Native>>
  public function getSocketType(): int;

  /**
   * Whether the socket is persistent
   *
   * @return boolean
   */
  <<__Native>>
  public function isPersistent(): bool;
}

<<__NativeData("ZMQPoll")>>
class ZMQPoll {
  /**
   * Add a new object into the poll set. Returns the id for the object
   * in the pollset.
   *
   * @param ZMQSocket|resource $object Object to add to set
   * @param integer $type Bit-mask of ZMQ::POLL_* constants
   *
   * @throws ZMQPollException if the object has not been initialized with polling
   * @return string
   */
  <<__Native>>
  public function add(mixed $object, int $type): string;

  /**
   * Removes an item from the poll object. The parameter can be ZMQ object,
   * resource or the string id returned by 'add' method. Returns true if the
   * item was removed and false if item had not been added to the poll object.
   *
   * @throws ZMQPollException if the poll object is empty
   * @throws ZMQPollException if $item parameter is object but not an instance of ZMQ
   *
   * @param mixed $item  The item to remove
   * @return boolean
   */
  <<__Native>>
  public function remove(mixed $item): bool;

  /**
   * Execute the poll. Readable and writable sockets are returned
   * in the arrays passed by reference. If either of the given arrays
   * is null the events of that type are not returned. Returns an integer
   * indicated the amount of objects with events pending.
   *
   * @param array &$readable   array where to return the readable objects
   * @param array &$writable   array where to return the writable objects
   * @param integer $timeout   Timeout for poll in microseconds. -1 polls as long as one of the objects comes readable/writable
   *
   * @throws ZMQPollException if polling fails
   * @return integer
   */
  <<__Native>>
  public function poll(mixed& $readable, mixed& $writable, int $timeout = -1): int;

  /**
   * Counts the items in the poll object
   *
   * @return integer
   */
  <<__Native>>
  public function count(): int;

  /**
   * Removes all items from the poll set
   *
   * @return ZMQPoll
   */
  <<__Native>>
  public function clear(): ZMQPoll;

  /**
   * Returns the ids of the objects that had ZMQ_POLLERR flag set on the last
   * poll call. This method does not clear the last errors and the errors are
   * cleared on next call to poll()
   *
   * @return array
   */
  <<__Native>>
  public function getLastErrors(): array;
}

/**
 * @EXTRA - This entire class is missing in the original.
 */
<<__NativeData("ZMQDevice")>>
class ZMQDevice {
  <<__Native>>
  public function __construct(ZMQSocket $frontend, ZMQSocket $backend, ?ZMQSocket $capture = null): void;
  <<__Native>>
  public function run(): void;
  <<__Native>>
  public function getIdleTimeout(): int;
  <<__Native>>
  public function setIdleTimeout(int $timeout): ZMQDevice;
  <<__Native>>
  public function getTimerTimeout(): int;
  <<__Native>>
  public function setTimerTimeout(int $timeout): ZMQDevice;
  <<__Native>>
  public function setIdleCallback(mixed $idle_callback, int $timeout, ?mixed $user_data = null): ZMQDevice;
  <<__Native>>
  public function setTimerCallback(mixed $idle_callback, int $timeout, ?mixed $user_data = null): ZMQDevice;
}