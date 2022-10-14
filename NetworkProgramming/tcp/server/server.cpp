//
// Created by shea on 1/6/22.
//
#include "server.h"
#include <cerrno>
#include <iomanip>

Server::Server(const std::string &port) {
    Port_ = port;
    IP_ = getLocalIP();
}

int Server::init() {
    //create socket
    lfd_ = socket(AF_INET,SOCK_STREAM,0);
    if (lfd_ < 0) {
        std::cerr << std::strerror(errno) << std::endl;
    }
    //bind
    struct sockaddr_in serv_addr{};
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9910);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = bind(lfd_, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        std::cerr << std::strerror(errno) << std::endl;
    }
    //listen
    listen(lfd_,128);

    //accept
    cfd_ = accept(lfd_, nullptr, nullptr);
    std::cout << "lfd:" << lfd_ << "cfd:" << cfd_ << std::endl;
    return 0;
}

void Server::info() const {
    std::cout << "The Server information as follows:" << std::endl;
    std::cout << std::setiosflags(std::ios::right);
    std::cout << std::setw(8) << "IP:" << std::setw(16) << IP_ << std::endl;
    std::cout << std::setw(8) << "Port:" << std::setw(16) << Port_ << std::endl;
}

std::string Server::getLocalIP() {
    const char* google_dns_server = "8.8.8.8";
    int dns_port = 53;

    struct sockaddr_in serv{};
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    //Socket could not be created
    if(sock < 0)
    {
        std::cout << "Socket error" << std::endl;
    }

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(google_dns_server);
    serv.sin_port = htons(dns_port);

    int err = connect(sock, (const struct sockaddr*)&serv, sizeof(serv));
    if (err < 0)
    {
        std::cout << "Error number: " << errno
                  << ". Error message: " << strerror(errno) << std::endl;
    }

    struct sockaddr_in name{};
    socklen_t nameLen = sizeof(name);
    err = getsockname(sock, (struct sockaddr*)&name, &nameLen);
    if (err < 0)
    {
        std::cout << "Error number: " << errno
                  << ". Error message: " << strerror(errno) << std::endl;
    }
    char buffer[INET_ADDRSTRLEN];
    const char* p = inet_ntop(AF_INET, &name.sin_addr, buffer, sizeof(buffer));
    if(p != nullptr)
    {
        std::cout << "Local IP address is: " << buffer << std::endl;
    } else {
        std::cout << "Error number: " << errno
                  << ". Error message: " << strerror(errno) << std::endl;
    }
    std::string IPStr(buffer);
    ::close(sock);
    return IPStr;
}

int Server::rev(std::vector<u_char> &data) {
    if (!data.empty()) {
        std::cerr << "warning: the vector used to receive is not empty" << std::endl;
    }
    worker = std::thread([this, &data]() {
        while(true) {
            size_t len; //to receive data
            size_t n;   //received data
            char buf[1024];
            //read data
            memset(buf, 0x00, sizeof(buf));
            n = read(cfd_, buf, sizeof(buf));
            if (n <= 0) {
                std::cerr << "read error or client exit." << std::endl;
                return;
            }
//            std::cout << "n:" << n << "buf:" << buf << std::endl;
            for (char & iter : buf) {
                data.emplace_back(iter);
            }
        }
    });
    return 0;
}

//int Server::send(const std::vector<u_char> &data) {
//    //send data
//    write(cfd_, buf, n);
//}

int Server::close() const {
    int retFlag = 0;
    if (::close(lfd_) == -1) {
        std::cout << "Error number: " << errno
                  << ". Error message: " << strerror(errno) << std::endl;
        retFlag = -1;
    }
    if (::close(cfd_) == -1) {
        std::cout << "Error number: " << errno
                  << ". Error message: " << strerror(errno) << std::endl;
        retFlag = -1;
    }
    return retFlag;
}

Server::~Server() {
    if (worker.joinable()) {
        worker.join();
    }
}

int main() {
    Server server;
    server.info();
    server.init();
    std::vector<u_char> revDate{};
    server.rev(revDate);
    for (auto &iter: revDate) {
        std::cout << iter;
    }
}