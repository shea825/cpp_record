cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(pythonLib)

find_package(PythonInterp REQUIRED)

find_package(PythonLibs REQUIRED)

add_executable(pythonLib pythonLib.cpp)

target_include_directories(pythonLib
        PRIVATE
        ${PYTHON_INCLUDE_DIRS}
        )

target_link_libraries(pythonLib
        PRIVATE
        ${PYTHON_LIBRARIES}
        )