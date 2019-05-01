cmake_minimum_required(VERSION 3.0)

project(hello)

set (CMAKE_CXX_FLAGS "--std=gnu++17")

find_package(Threads)

include_directories(hello PRIVATE ./src)

set(SRCS ./test/main.cpp)

add_executable(test.out ${SRCS})

target_link_libraries(test.out ${CMAKE_THREAD_LIBS_INIT})