cmake_minimum_required(VERSION 2.8.12)
PROJECT(Babel)

add_definitions("-std=c++14 -g3")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_subdirectory(Server)
add_subdirectory(Client)