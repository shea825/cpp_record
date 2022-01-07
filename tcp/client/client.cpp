//
// Created by shea on 1/6/22.
//
#include <iomanip>

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
    return 0;
}
int Client::close() {
    ::close(cfd_);
    return 0;
}
void Client::info() {
    std::cout << "The client information as follows:" << std::endl;
    std::cout << std::setiosflags(std::ios::right);
    std::cout << std::setw(8) << "Ip:" << std::setw(12) << IP_ << std::endl;
    std::cout << std::setw(8) << "Port:" << std::setw(12) << Port_ << std::endl;
}
int Client::send(const std::vector<u_char> data) {

    worker = std::thread([this, &data]() {
        size_t len;
        size_t n;
        char buf[1024];
        auto iter = data.begin();
        while (true) {
            //split data
//            n = read(STDIN_FILENO, buf, sizeof(buf));
            memset(buf, 0x00, sizeof(buf));
            len = (data.end()-iter+1 > 1024) ? 1024 : data.end()-iter+1;
            std::copy(iter, (len == 1024) ? iter+1023 : data.end(), buf);
            //send data
            n = write(cfd_, buf, len);
            if (n <= 0) {
                std::cerr << "send error or server exit." << std::endl;
                return;
            }
        }
    });
    return 0;
}
int main() {
    Client clientInstance;
    clientInstance.connect();
    clientInstance.info();
    return EXIT_SUCCESS;
}

