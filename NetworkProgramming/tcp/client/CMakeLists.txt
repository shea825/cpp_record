project(tcpClient)
add_executable(tcpClient client.cpp client.h)
target_link_libraries(tcpClient pthread)