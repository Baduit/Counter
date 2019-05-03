cmake_minimum_required(VERSION 3.0)

project(hello)

add_definitions(-std=c++17 -Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith) 

find_package(Threads)

include_directories(hello PRIVATE ./src)

set(SRCS ./test/main.cpp)

add_executable(test.out ${SRCS})

target_link_libraries(test.out ${CMAKE_THREAD_LIBS_INIT})