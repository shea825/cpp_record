
/** @file UringNet.cpp
 *  @author shea
 *  @date 10:26 AM 5/23/22
 *  @plat CLion
 *  @brief this is a 
 */

#include <cstdio>
#include <cstring>
#include "UringNet.h"
#include "../include/muduo/Socket.h"

UringNet::UringNet(int QUEUE_DEPTH, long BLOCK_SZ) {
    this->QD_ = QUEUE_DEPTH;
    this->BS_ = BLOCK_SZ;
}

int UringNet::init() {
    int ret;
    ret = io_uring_queue_init(QD_, &ring_, 0);
    if( ret < 0) {
        fprintf(stderr, "queue_init: %s\n", strerror(-ret));
        return -1;
    }
    return 0;
}

void UringNet::get_status() const {
    printf("QUEUE_DEPTH: %d\nBLOCK_SZ: %ld\n", QD_, BS_);
}

int UringNet::setup_listen(int port) {
    int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("socket error");
    }

    sockets_.insert({socket_fd, std::make_unique<Socket>(socket_fd)});
    inetAddresses_.insert({socket_fd, InetAddress(port)});

    sockets_.at(socket_fd)->setReuseAddr(true);


    sockets_.at(socket_fd)->bindAddress(inetAddresses_.at(socket_fd));
    sockets_.at(socket_fd)->listen();

    return socket_fd;
}

int UringNet::add_accpet_request() {
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring_);

//    io_uring_prep_accept(sqe, socket_->fd(), inetAddress_.getSockAddr(),
//                         , 0);
}



