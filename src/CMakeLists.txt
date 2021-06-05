project(YASW) # Yet Another Socket Wrapper
cmake_minimum_required(VERSION 3.0)

find_package(fmt)

add_library(yasw STATIC serversocket.cpp serversocket.h)

add_executable(example example.cpp)

target_link_libraries(example yasw fmt)

