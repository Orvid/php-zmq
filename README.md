This is a port of the PHP extension for ZMQ to HHVM using HNI.

This was started due to the ownership of the code of the only existing implementation for HHVM, originally [here](https://github.com/yybirdcf/zmq-extension-for-hhvm) and then, through some fun, the updated version ended up in a non-forked copy of the repo [here](https://github.com/no1youknowz/hhvm-zeromq-ext), being very uncertain, making it impossible for it to ever be brought into the main repo as a supported extension.

The extra functionality that is enabled by the use of [CZMQ](http://czmq.zeromq.org/) with the original PECL extension is supported.

There are 3 tests that fail under MSVC due to things not being implemented yet, or else won't be supported under MSVC:
- 007 - Currently requires `stream_socket_server` to work.
- g59 - Requires `fork`
- g59_2 - Requires `fork`

There are 5 tests that fail due to differences between HHVM and PHP:
- 019 - Can't add an overload for the deprecated signature with HHVM.
- 030 - Fails due to not having poked the test runner to get it to evaluate the skip correctly.
- 037 - Tries to construct a `ZMQDevice` and use the deprecated form of `setIdleCallback`.
- 038 - Tries to destruct an uninitalized object. Once [HHVM#6215](https://github.com/facebook/hhvm/issues/6215) is fixed, this should no longer be an issue.
- g43 - Fails due to difference in messages between HHVM and PHP.

The other 45 test pass.

This makes 45/50 valid tests passing under MSVC.
