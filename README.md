This is a port of the PHP extension for ZMQ to HHVM using HNI.

This was started due to the ownership of the code of the only existing implementation for HHVM, originally [here](https://github.com/yybirdcf/zmq-extension-for-hhvm) and then, through some fun, the updated version ended up in a non-forked copy of the repo [here](https://github.com/no1youknowz/hhvm-zeromq-ext), being very uncertain, making it impossible for it to ever be brought into the main repo as a supported extension.

Currently the extra functionality in the PECL extension that was enabled by the use of [CZMQ](http://czmq.zeromq.org/) is not supported. This may be supported at some point in the future, but was ignored completely when doing the original port.


Need to implement `ZMQPollData::add` with Resources.

Need to implement `ZMQSocket->getSockOpt` with a key of `ZMQ_FD`.
