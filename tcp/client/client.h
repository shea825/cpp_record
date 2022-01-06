//
// Created by shea on 1/6/22.
//

#ifndef MAINPROJ_CLIENT_H
#define MAINPROJ_CLIENT_H

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

class Client {
public:
    explicit Client(const std::string& IP = "127.0.0.1", const std::string& Port = "8888");
    static int connect();
    static int close();
    void info();
private:
    const static char *const IP_;
    const static unsigned short Port_;
    static int cfd_;
};
#endif //MAINPROJ_CLIENT_H
