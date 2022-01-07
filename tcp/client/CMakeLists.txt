project(tcpClient)
add_executable(tcpClient client.cpp client.h)
set(CMAKE_CXX_STANDARD 17)
target_link_libraries(tcpClient pthread)