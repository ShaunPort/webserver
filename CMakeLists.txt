cmake_minimum_required(VERSION 2.8)
project(webserver)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src bin)


add_executable(EpollerTest test/EpollerTest.cpp)
