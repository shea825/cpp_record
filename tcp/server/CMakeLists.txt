project(tcpServer)
add_executable(tcpServer server.cpp server.h)
target_link_libraries(${PROJECT_NAME} pthread)