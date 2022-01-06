//
// Created by shea on 1/6/22.
//
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
int main() {
    //create socket
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    if (lfd < 0) {
        std::cerr << "socket create error. " << std::endl;
        return -1;
    }
    //bind
    struct sockaddr_in serv_addr{};
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        std::cerr << "bind error. " << std::endl;
        return -1;
    }
    //listen
    listen(lfd,128);

    //accept
    int cfd = accept(lfd, nullptr, nullptr);
    std::cout << "lfd:" << lfd << "cfd:" << cfd << std::endl;

    size_t n;
    char buf[1024];

    while(true) {
        //read data
        memset(buf, 0x00, sizeof(buf));
        n = read(cfd, buf, sizeof(buf));
        if (n <= 0) {
            std::cerr << "read error or client exit." << std::endl;
            break;
        }
        std::cout << "n:" << n << "buf:" << buf << std::endl;
        for (int i = 0; i < n; ++i) {
            buf[i] = (char)toupper(buf[i]);
        }
        //send data
        write(cfd, buf, n);
    }
    close(lfd);
    close(cfd);
}
