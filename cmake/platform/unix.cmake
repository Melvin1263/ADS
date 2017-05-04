if(CMAKE_C_COMPILER MATCHES "gcc" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
	include("${CMAKE_SOURCE_DIR}/cmake/platform/compiler/gcc.cmake")
endif()