
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

UringNet::~UringNet() {
    io_uring_queue_exit(&ring_);
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

    //bind and listen
    sockets_.at(socket_fd)->bindAddress(inetAddresses_.at(socket_fd));
    sockets_.at(socket_fd)->listen();

    return socket_fd;
}

int UringNet::add_accept_request(int fd) {
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring_);
    auto* client_addr = const_cast<sockaddr *>(inetAddresses_.at(fd).getSockAddr());
    socklen_t client_len = sizeof(*client_addr);
    io_uring_prep_accept(sqe, fd, client_addr,
                         &client_len, 0);
    auto req = std::make_shared<struct request>();
    req->event_type = req_accept;
    io_uring_sqe_set_data(sqe, req.get());
    io_uring_submit(&ring_);
    return 0;
}

void UringNet::server(int fd, const callbackFunc& handle_client_request) {
    struct io_uring_cqe *cqe;
    add_accept_request(fd);
    while (true) {
        int ret = io_uring_wait_cqe(&ring_, &cqe);
        auto *req = (struct request *) cqe->user_data;
        if (ret < 0)
            perror("io_uring_wait_cqe");
        if (cqe->res < 0) {
            fprintf(stderr, "Async request failed: %s for event: %d\n",
                    strerror(-cqe->res), req->event_type);
            exit(1);
        }
        switch (req->event_type) {
            case req_accept:
                add_accept_request(fd);
                add_read_request(cqe->res);
                free(req);
                break;
            case req_read:
                if (!cqe->res) {
                    fprintf(stderr, "Empty request!\n");
                    break;
                }
                handle_client_request(req->get_msg());
                free(req->iov[0].iov_base);
                free(req);
                break;
            case req_write:
                for (int i = 0; i < req->iovec_count; i++) {
                    free(req->iov[i].iov_base);
                }
                free(req);
                break;
        }
        /* Mark this request as processed */
        io_uring_cqe_seen(&ring_, cqe);
    }
}

int UringNet::add_read_request(int fd) {
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring_);
    auto req = std::make_shared<struct request>();
    req->iov[0].iov_base = malloc(BS_);
    req->iov[0].iov_len = BS_;
    req->event_type = req_read;
    req->client_socket = fd;
    memset(req->iov[0].iov_base, 0, BS_);
    io_uring_prep_readv(sqe, fd, &req->iov[0], 1, 0);
    io_uring_sqe_set_data(sqe, req.get());
    io_uring_submit(&ring_);
    return 0;
}

int UringNet::add_write_request(struct request *req) {
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring_);
    req->event_type = req_write;
    io_uring_prep_writev(sqe, req->client_socket, req->iov, req->iovec_count, 0);
    io_uring_sqe_set_data(sqe, req);
    io_uring_submit(&ring_);
    return 0;
}

std::string request::get_msg() {
    return std::string((char *)iov[0].iov_base, iov[0].iov_len);
}
