
/** @file UringNet.h
 *  @author shea
 *  @date 10:26 AM 5/23/22
 *  @plat CLion
 *  @brief this is a simple net lib based on liburing
 */

#pragma once

#include <liburing.h>
#include <map>
#include <memory>
#include "../include/muduo/Socket.h"
#include "../include/muduo/SocketOps.h"

struct request {
    int event_type;
    int iovec_count;
    int client_socket;
    struct iovec iov[];
};
using inetAddresses = std::map<int, InetAddress>;//inetAddress map
using sockets = std::map<int, std::unique_ptr<Socket>>;//socket map

class UringNet {
private:
    int QD_;
    long BS_;
    static const int default_port = 8000;
    struct io_uring ring_{};
    sockets sockets_;
    inetAddresses inetAddresses_;

public:
    explicit UringNet(int QUEUE_DEPTH = 256, long BLOCK_SZ = 8*1024);
    ~UringNet() = default;
    int init();

    void get_status() const;

    int setup_listen(int port = default_port);
    int add_accpet_request();
};



