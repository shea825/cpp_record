cmake_minimum_required(VERSION 3.19)
project(unicast)

set(CMAKE_CXX_STANDARD 11)

add_executable(UDPUnicast UDPUnicast.cpp)

add_executable(NonCopyable NonCopyable.cpp)