cmake_minimum_required(VERSION 3.0)

project(hello)

set (CMAKE_CXX_FLAGS "--std=gnu++17")

include_directories(hello PRIVATE ./src)

set(SRCS ./test/main.cpp)

add_executable(test.out ${SRCS})