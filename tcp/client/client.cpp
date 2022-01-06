//
// Created by shea on 1/6/22.
//
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <iomanip>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "client.h"
Client::Client(const std::string& IP, const std::string& Port) {//constructor
    auto* p = (std::string*)&(Client::IP_);
    *p = IP;
    p = (std::string*)&(Client::Port_);
    *p = Port;
}
int Client::connect() {
    //create socket
    cfd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (cfd_ < 0) {
        std::cerr << "socket error." << std::endl;
        return -1;
    }
    //connect server
    struct sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(Port_);
    inet_pton(AF_INET, IP_, &serv_addr.sin_addr.s_addr);
    printf("[%x]\n",serv_addr.sin_addr.s_addr);
    int ret = ::connect(cfd_, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        std::cerr << "connect error." << std::endl;
        return -1;
    }
}
int Client::close() {
    ::close(cfd_);
}
void Client::info() {
    std::cout << "The client information as follows:" << std::endl;
    std::cout << std::setiosflags(std::ios::right);
    std::cout << std::setw(8) << "Ip:" << std::setw(12) << IP_ << std::endl;
    std::cout << std::setw(8) << "Port:" << std::setw(12) << Port_ << std::endl;
}
int main() {
    int n;
    char buf[1024];
    while (true) {
        //read data
        memset(buf, 0x00, sizeof(buf));
        n = read(STDIN_FILENO, buf, sizeof(buf));
        //send data
        write(cfd_, buf, n);
        //read data
        memset(buf, 0x00, sizeof(buf));
        n = read(cfd_, buf, sizeof(buf));
        if (n <= 0) {
            std::cerr << "read error or server exit." << std::endl;
            break;
        }
        std::cout << "n:" << n << "buf:" << buf << std::endl;
    }

    return 0;
}

