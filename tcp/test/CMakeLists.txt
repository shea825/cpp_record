project(tcpUTest)
find_program(BASH_EXECUTABLE NAMES bash REQUIRED)
add_executable(tcpUTest test.cpp)
enable_testing()
add_test(
        NAME tcpUTest
        COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.sh

)