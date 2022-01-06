cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(boostLib)

find_package(Boost 1.54 REQUIRED COMPONENTS filesystem)
add_executable(boostLib boostLib.cpp)
target_link_libraries(boostLib
        PUBLIC
        Boost::filesystem)