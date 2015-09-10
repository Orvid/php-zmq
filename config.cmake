if (EXT_ZMQ_IN_TREE_BUILD)
  # You shouldn't normally be building this way. This
  # is just to make my local dev process easier.
  include_directories("F:/Libraries/libzmq/include")
  link_libraries(debug;F:/Libraries/libzmq/lib/libzmqMTd.lib;debug;F:/Libraries/libzmq/lib/libsodiumMTd.lib;debug;F:/Libraries/libzmq/lib/libczmqMTd.lib;optimized;F:/Libraries/libzmq/lib/libzmqMT.lib;optimized;F:/Libraries/libzmq/lib/libsodiumMT.lib;optimized;F:/Libraries/libzmq/lib/libczmqMT.lib)
  link_libraries(Rpcrt4.lib)
  add_definitions("-DHAVE_LIBZMQ")
  add_definitions("-DHAVE_LIBCZMQ")
  add_definitions("-DZMQ_STATIC")
  add_definitions("-DLIBCZMQ_STATIC")

  HHVM_DEFINE_EXTENSION("zmq"
    SOURCES
      ext_zmq.cpp
      zmq_sockopt.cpp
    HEADERS
      ext_zmq.h
      ext_zmq-private.h
    SYSTEMLIB
      ext_zmq.php
  )
else()
  HHVM_EXTENSION(zmq ext_zmq.cpp zmq_sockopt.cpp ext_zmq.h ext_zmq-private.h)
  HHVM_SYSTEMLIB(zmq ext_zmq.php)

  FIND_PATH(ZMQ_INCLUDE_DIR NAMES zmq.h PATHS /usr/include /usr/local/include)
  FIND_LIBRARY(ZMQ_LIBRARY NAMES zmq PATHS /lib /usr/lib /usr/local/lib)

  FIND_PATH(CZMQ_INCLUDE_DIR NAMES czmq.h PATHS /usr/include /usr/local/include)
  FIND_LIBRARY(CZMQ_LIBRARY NAMES czmq PATHS /lib /usr/lib /usr/local/lib)
  FIND_LIBRARY(SODIUM_LIBRARY NAMES sodium PATHS /lib /usr/lib /usr/local/lib)

  if (CZMQ_INCLUDE_DIR AND CZMQ_LIBRARY AND SODIUM_LIBRARY)
    add_definitions("-DHAVE_LIBCZMQ=1")
    include_directories(${CZMQ_INCLUDE_DIR})
    target_link_libraries(zmq, ${CZMQ_LIBRARY})
    target_link_libraries(zmq, ${SODIUM_LIBRARY})
  endif()

  include_directories(${ZMQ_INCLUDE_DIR})
  target_link_libraries(zmq ${ZMQ_LIBRARY})
endif()
