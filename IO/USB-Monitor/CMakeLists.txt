cmake_minimum_required(VERSION 3.19)
project(USB_Monitor)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_executable(USB_Monitor USB_Monitor.cpp)

add_subdirectory(drv)