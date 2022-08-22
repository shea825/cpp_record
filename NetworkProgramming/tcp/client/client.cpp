//
// Created by shea on 1/6/22.
//
#include <iomanip>
#include <netinet/tcp.h>

#include "client.h"
Client::Client(const std::string& ip, const std::string& port) {//constructor
    IP_ = ip;
    Port_ = port;
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
    serv_addr.sin_port = htons(strtol(Port_.c_str(), nullptr, 10));//unsigned short int
    inet_pton(AF_INET, IP_.c_str(), &serv_addr.sin_addr.s_addr);
    printf("[%x]\n",serv_addr.sin_addr.s_addr);
    int ret = ::connect(cfd_, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        std::cerr << "connect error." << std::endl;
        return -1;
    }
    return 0;
}
int Client::close() const {
    return ::close(cfd_);
}
void Client::info() const{
    std::cout << "The client information as follows:" << std::endl;
    std::cout << std::setiosflags(std::ios::right);
    std::cout << std::setw(8) << "Ip:" << std::setw(12) << IP_ << std::endl;
    std::cout << std::setw(8) << "Port:" << std::setw(12) << Port_ << std::endl;
}
int Client::loopSend(std::vector<u_char> data) {

    worker = std::thread([this, &data]() {
        size_t len; //to write length
        size_t n;   //writen length
        char buf[1024];
        auto iter = data.begin();
        while (true) {
//            n = read(STDIN_FILENO, buf, sizeof(buf));
            //split data
            memset(buf, 0x00, sizeof(buf));
            len = (data.end()-iter+1 > 1024) ? 1024 : data.end()-iter+1;
            std::copy(iter, (len == 1024) ? iter+1023 : data.end(), buf);
            iter = (len == 1024) ? iter+1023 : data.end();  //update iter
            //send data
            n = write(cfd_, buf, len);
            if (n <= 0) {
                std::cerr << "send error or server exit." << std::endl;
                return;
            } else if (iter == data.end()) {
                std::cout << "send data complete" << std::endl;
                return;
            }
        }
    });
    return 0;
}

int Client::rev(std::vector<u_char> &data) {
    return 0;
}

Client::~Client() {
    struct tcp_info info{};
    int len=sizeof(info);
    getsockopt(cfd_, IPPROTO_TCP, TCP_INFO, &info, (socklen_t *)&len);
    if(info.tcpi_state == TCP_ESTABLISHED) {
        close();
    }
    if (worker.joinable()) {
        worker.join();
    }
}

int Client::send(std::string data) {
    char* buf = data.data();
    size_t bufSize = data.size();
    size_t n = write(cfd_, buf, bufSize);
    if (n <= 0) {
        std::cerr << "send error or server exit." << std::endl;
        return -1;
    }
    std::cout << "send success. buf: " << data << std::endl
              << "size: " << bufSize << std::endl;
}

int main() {
    Client client("127.0.0.1", "5188");
    client.info();
    client.connect();
    client.send("123412345678910");
    client.send("abcdefg");
    client.send("[]-=]==========");
    return EXIT_SUCCESS;
}

