//
// Created by shea on 2/18/22.
//

#ifndef MAINPROJ_SERVER_H
#define MAINPROJ_SERVER_H

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>

class Server {
public:
    explicit Server(const std::string& port = "8888");
    int init();
    void info() const;
    int close() const;
    int rev(std::vector<u_char> &data);
    int send(const std::vector<u_char> &data);
    ~Server();

private:
    std::string IP_;
    std::string Port_;
    int lfd_{};
    int cfd_{};
    std::thread worker;
    static std::string getLocalIP();
};

#endif //MAINPROJ_SERVER_H
