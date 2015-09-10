<?hh

/**
 * @EXTRA - None of these exceptions are defined in the original.
 */
class ZMQException extends Exception { }
final class ZMQAuthException extends ZMQException { }
final class ZMQCertException extends ZMQException { }
final class ZMQContextException extends ZMQException { }
final class ZMQDeviceException extends ZMQException { }
final class ZMQSocketException extends ZMQException { }
final class ZMQPollException extends ZMQException { }

/**
 * @EXTRA - Everything in this is extra.
 */
class ZMQ {
  private final function __construct() {}

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
  public final function __construct(int $io_threads = 1, bool $is_persistent = true): void;

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
  public final function __construct(ZMQContext $context, int $type, ?string $persistent_id = null, ?mixed $on_new_socket = null): void;

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
  <<__Native>>
  public function sendMsg(string $message, int $flags = 0): mixed;

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
  <<__Native>>
  public function recvMsg(int $flags = 0): mixed;

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
  public final function __construct(ZMQSocket $frontend, ZMQSocket $backend, ?ZMQSocket $capture = null): void;
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

/**
 * A security certificate for the ØMQ CURVE authentication mechanism.
 */
<<__NativeData("ZMQCert")>>
class ZMQCert {
    /**
     * Constructs a new instance of the ZMQCert class.
     *
     * If the filename parameter is given and is a readable file, then the
     * security certificate is initialised with the public and secret keys and
     * metadata in the file.
     *
     * Note well that if the file only contains a public key, then the secret
     * key won't be initialised but the security certificate can be applied to a
     * socket without error.
     *
     * If the filename parameter isn't given, then the security certificate is
     * initialised with randomly generated public and secret keys.
     *
     * @final
     *
     * @param string $filename
     * @throws ZMQCertException If the filename parameter isn't a string or
     *     can't be converted to a string
     * @throws ZMQCertException If the underlying zcert object can't be
     *     created, which is likely if libsodium isn't installed
     * @throws ZMQCertException If the file isn't readable or isn't in the
     *     {@link ZMQCert#save} format
     */
    <<__Native>>
    public final function __construct(?string $filename = null): void;

    /**
     * Gets the public key as a 32-byte binary string.
     *
     * @return string
     */
    <<__Native>>
    public function getPublicKey(): string;

    /**
     * Gets the secret key as a 32-byte binary string.
     *
     * @return string
     */
    <<__Native>>
    public function getSecretKey(): string;

    /**
     * Gets the public key as a Z85 armoured string.
     *
     * @return string
     */
    <<__Native>>
    public function getPublicTxt(): string;

    /**
     * Gets the secret key as a Z85 armoured string.
     *
     * @return string
     */
    <<__Native>>
    public function getSecretTxt(): string;

    /**
     * Sets the metadata value.
     *
     * @param string $name The name of the metadata value
     * @param string $format The metadata value
     */
    <<__Native>>
    public function setMeta(string $name, string $format): void;

    /**
     * Gets the metadata value.
     *
     * @param string $name The name of the metadata value
     * @return string|null If the metadata value exists, then it is returned;
     *     otherwise null
     */
    <<__Native>>
    public function getMeta(string $name): ?string;

    /**
     * Gets the names of all of the metadata values.
     *
     * Note well that the names of the metadata values are returned in the
     * opposite order that they are registered.
     *
     * <code>
     * $cert = new ZMQCert();
     * $cert->setMeta('one', '1');
     * $cert->setMeta('two', '2');
     * $cert->getMetaNames(); => ['two', 'one']
     * </code>
     *
     * @return array The names of all of the metadata values
     */
    <<__Native>>
    public function getMetaKeys(): array;

    /**
     * Saves the public key and metadata to the specified file.
     *
     * @param string $filename
     * @throws ZMQCertException If the file isn't writeable
     */
    <<__Native>>
    public function savePublic(string $filename): void;

    /**
     * Saves the secret key and metadata to the specified file.
     *
     * @param string $filename
     * @throws ZMQCertException If the file isn't writeable
     */
    <<__Native>>
    public function saveSecret(string $filename): void;

    /**
     * Saves the public and secret keys and metadata to the specified file.
     *
     * @param string $filename
     * @throws ZMQCertException If the file isn't writeable
     */
    <<__Native>>
    public function save(string $filename): void;

    /**
     * Applies the security certificate to the socket by setting the
     * {@link ZMQ::CURVE_PUBLICKEY_BIN} and {@link ZMQ::CURVE_SECRETKEY_BIN}
     * socket options to the public and secret keys respectively.
     *
     * @param ZMQSocket $socket
     */
    <<__Native>>
    public function apply(ZMQSocket $socket): void;

    /**
     * Tests whether the security certificate is equal to another.
     *
     * Two security certificates are equal iff their public and secret keys are
     * equal.
     *
     * @param ZMQCert $certificate
     * @return boolean
     */
    <<__Native>>
    public function equals(ZMQCert $certificate): bool;
}

/**
 * A ØMQ authentication handler, which takes over authentication for all
 * incoming connections for a context.
 *
 * ØMQ has four authentication mechanisms: NULL, authenticated NULL, PLAIN,
 * and CURVE.
 *
 * The default authentication mechanism is NULL, which an
 * authentication handler doesn't receive authentication requests for.
 *
 * If a socket, that has a context with an authentication handler, has a ZAP
 * domain (the {@link ZMQ::SOCKOPT_ZAP_DOMAIN} socket option is set), then the
 * authentication handler receives authentication requests for incoming
 * connections to that socket, hence "authenticated NULL".
 *
 * In both the PLAIN and CURVE authentication mechanisms the authentication
 * handler tests the authentication credentials of the incoming connection.
 */
<<__NativeData("ZMQAuth")>>
class ZMQAuth {
    /**
     * Constructs a new instance of the ZMQAuth class.
     *
     * @param ZMQContext $context
     * @throws ZMQAuthException If the underlying zauth object can't be
     *     created
     */
    <<__Native>>
    public final function __construct(ZMQContext $context): void;

    /**
     * Allow (whitelist) a single IP address.
     *
     * All incoming connections from the IP address will be accepted by the NULL
     * authentication mechanism and will be allowed to continue authenticating
     * in the PLAIN and CURVE authentication mechanisms.
     *
     * Note well that if you whitelist a single address, then any non-
     * whitelisted addresses are treated as if they were blacklisted.
     *
     * @param string $address
     * @return ZMQAuth Provides a fluent interface
     */
    <<__Native>>
    public function allow(string $address): ZMQAuth;

    /**
     * Deny (blacklist) a single IP address.
     *
     * All incoming connections from the IP address will be rejected by all
     * authentication mechanisms.
     *
     * Note well that if you define a whitelist and a blacklist then only the
     * whitelist will be used to authenticate incoming connections.
     *
     * @param string $address
     * @return ZMQAuth Provides a fluent interface
     */
    <<__Native>>
    public function deny(string $address): ZMQAuth;

    /**
     * Configure the PLAIN or CURVE authentication mechanism for the ZAP domain.
     *
     * When configuring the PLAIN authentication mechanism the filename
     * parameter should be the filename of a plain-text password file.
     *
     * @see examples/woodhouse.php
     *
     * When configuring the CURVE authentication mechanism the filename
     * parameter should be the path of the directory that contains valid public
     * keys.
     *
     * @param integer $type {@link ZMQAuth::PLAIN} to configure the PLAIN
     *     authentication mechanism or {@link ZMQAuth::CURVE} to configure the
     *     CURVE authentication mechanism
     * @param string $domain The ZAP domain. Use "*" to configure the PLAIN or
     *     CURVE authentication mechanism for all domains
     * @param string $filename
     * @return ZMQAuth Provides a fluent interface
     */
    <<__Native>>
    public function configure(int $type, string $domain, string $filename): ZMQAuth;
}
