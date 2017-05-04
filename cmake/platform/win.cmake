if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
	include("${CMAKE_SOURCE_DIR}/cmake/platform/compiler/msvc.cmake")
endif()