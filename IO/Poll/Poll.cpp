//
// Created by shea on 8/8/22.
//
#include <csignal>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main() {
    signal(SIGPIPE, SIG_IGN);   //如果客户端close套接字后，服务器调用一次write会收到RST，若再次调用write，会产生SIGPIPE信号
    /**尽可能避免服务端进行TIME_WAIT状态
     * 如果服务端主动断开连接（先于客户端close），服务端会进行TIME_WAIT状态
     * 协议设计上，应该让客户端主动断开连接
     * 同时服务端也应有一个机制，让不活跃客户端的主动close
     */
    signal(SIGCHLD, SIG_IGN);    //表示父进程忽略SIGCHLD信号，不让父进程挂起，该信号是子进程退出的时候向父进程发送的

    int listenfd;

    listenfd = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (listenfd < 0) {
        std::cerr << std::strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }
}