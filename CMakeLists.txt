cmake_minimum_required(VERSION 3.15)
project(mainProj)
add_executable(mainProj main.cpp)

if(NOT WIN32)
    add_definitions(-fPIC)
endif()

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(processorInfo)

find_package(PythonLibs)
if (PythonLibs_FOUND)
    add_subdirectory(pythonLib)
    message(STATUS "Python Lib Found")
endif ()

add_subdirectory(matrix)

find_package(Boost)
if (Boost_FOUND)
    add_subdirectory(boostLib)
    message(STATUS "Boost Lib Found")
endif ()


add_subdirectory(IO)

option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

add_subdirectory(designPatterns)

add_subdirectory(Features)
add_subdirectory(Algorithm)
add_subdirectory(NetworkProgramming)
add_subdirectory(Thinkings)
add_subdirectory(STL)
add_subdirectory(utils)

if (ENABLE_UNIT_TESTS)
    enable_testing()

    add_test(
            NAME matrixTest
            COMMAND matrixTest
    )

endif ()

