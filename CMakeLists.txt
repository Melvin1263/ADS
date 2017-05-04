cmake_minimum_required(VERSION 3.4)

# Projectname
project(ADSPraktikum)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set macro directory
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros")

# Bin and lib output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Options
option(BUILD_PRAK_1 "Build project files for 'Praktkium 1'" 1)
option(BUILD_PRAK_2 "Build project files for 'Praktkium 2'" 1)

# Macro AutoCollect
include(AutoCollect)

# Macro CheckPlatform
include(CheckPlatform)

if(BUILD_PRAK_1)
    add_subdirectory(Praktikum_1)
endif()
if(BUILD_PRAK_1)
    add_subdirectory(Praktikum_2)
endif()
