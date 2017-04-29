cmake_minimum_required(VERSION 3.7)

# Projectname
project(Praktikum_2)

# Set macro directory
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake/macros")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Macro AutoCollect
include(AutoCollect)

# Unterordner
add_subdirectory(Aufgabe_2_2)
add_subdirectory(Aufgabe_2_3)
add_subdirectory(Aufgabe_2_4)