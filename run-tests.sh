#! /bin/sh

export TEST_PHP_EXECUTABLE="hhvm"
hhvm -vDynamicExtensions.0=zmq.so "run-tests.php" tests/*.phpt
