#include <iostream>
#include <functional>
#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>
#include <atomic>

std::atomic_bool stopped = {false};

void udp_unicast_recv(const std::string &self_ip, uint32_t udp_recv_port,
                      const std::function<void(const char *, ssize_t)> &callback) {
    const char *ip = self_ip.c_str();
    struct sockaddr_in local_address{}, peer_addr{};
    int sockfd;
    unsigned char loop;
    const auto BUFLEN = 256;
    char recmsg[BUFLEN];
    ssize_t socklen, n;
    struct ip_mreq mreq{};

/* 创建 socket 用于UDP通讯 */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creating err in multicast_recv\n");
        return;
    }

    socklen = sizeof(struct sockaddr_in);
    memset(&local_address, 0, socklen);
    local_address.sin_family = AF_INET;
    local_address.sin_port = htons(udp_recv_port);
    inet_pton(AF_INET, ip, &local_address.sin_addr);
    if (bind(sockfd, (struct sockaddr *) &local_address, sizeof(struct sockaddr_in)) == -1) {
        perror("bind error\n");
        return;
    }
    struct timeval tv{};
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        perror("set timeout error");
        return;
    }
    while (!stopped) {
        bzero(recmsg, BUFLEN);
        n = recvfrom(sockfd, recmsg, BUFLEN, 0, (struct sockaddr *) &peer_addr, (socklen_t *) &socklen);
        if (n <= 0) {
            if (errno == EAGAIN) {
                continue;
            }
            perror("recvfrom err in unicast_recv!\n");
            const char *peer_ip = inet_ntoa(peer_addr.sin_addr);
            int peer_port = ntohs(peer_addr.sin_port);
            std::cerr << "endpoint error: " << peer_ip << ":" << peer_port;
            return;
        } else {
            recmsg[n] = 0;
        }
        callback(recmsg, n);
    }
}

int main() {
    udp_unicast_recv("127.0.0.1", 6679,  [](const char *data, int size) {
        std::cout << std::string(data, size) << std::endl;
    });
    return 0;
}
