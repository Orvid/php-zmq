This is a port of the PHP extension for ZMQ to HHVM using HNI.

This was started due to the ownership of the code of the only existing implementation for HHVM, originally [here](https://github.com/yybirdcf/zmq-extension-for-hhvm) and then, through some fun, the updated version ended up in a non-forked copy of the repo [here](https://github.com/no1youknowz/hhvm-zeromq-ext), being very uncertain, making it impossible for it to ever be brought into the main repo as a supported extension.

Currently the extra functionality in the PECL extension that was enabled by the use of [CZMQ](http://czmq.zeromq.org/) is not supported. This may be supported at some point in the future, but was ignored completely when doing the original port.


Need to implement `ZMQPollData::add` with Resources.

Need to implement `ZMQSocket->getSockOpt` with a key of `ZMQ_FD`.


There are 3 tests that fail under MSVC due to things not being implemented yet, or else won't be supported under MSVC:
007 - Currently requires `stream_socket_server` to work.
g59 - Requires `fork`
g59_2 - Requires `fork`

There are 3 tests that fail due to differences between HHVM and PHP:
019 - Can't add an overload for the deprecated signature with HHVM.
030 - Fails due to not having poked the test runner to get it to evaluate the skip correctly.
g43 - Fails due to difference in messages between HHVM and PHP.

There are 4 tests that are known to be failing currently:
022 - Highwater mark isn't working right
036 - Destruction of ZMQDevice is having problems
037 - Same as 036.
g50 - Some issues with polling. Might be related to 022.

There are 10 tests that fail due to `ZMQCert` and `ZMQAuth` not yet being implemented:
038, 039, 040, 041, 042, 043, 044, 045, 046, and 047

The other 33 test pass.

This makes 39/43 valid tests passing.
