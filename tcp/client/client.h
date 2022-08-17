//
// Created by shea on 1/6/22.
//

#ifndef MAINPROJ_CLIENT_H
#define MAINPROJ_CLIENT_H

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>

class Client {
public:
    explicit Client(const std::string& ip = "127.0.0.1", const std::string& port = "8888");
    int connect();
    int close() const;
    void info() const;
    int loopSend(std::vector<u_char> data);
    int send(std::string data);
    int rev(std::vector<u_char> &data);
    ~Client();
private:
    std::string IP_;
    std::string Port_;
    int cfd_{};
    std::thread worker;
};
#endif //MAINPROJ_CLIENT_H
