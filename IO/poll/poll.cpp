//
// Created by shea on 8/8/22.
//
#include <csignal>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/poll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define ERR_EXIT( FUNC ) \
    std::cerr << std::strerror(errno) << #FUNC << std::endl; \
    return EXIT_FAILURE

using PollFdList = std::vector<struct pollfd>;

#define BufLen 1024

#define PORT 5188

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
    //非阻塞+IO复用
    //替换的时候 文件描述符处于 关闭 状态
    if (listenfd < 0) {
        ERR_EXIT(socket);
    }

    struct sockaddr_in servaddr{};
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /**
     * 设置地址的重复利用
     */
    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        ERR_EXIT(setsockopt);
    }

    /**
     * 绑定
     */
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        ERR_EXIT(bind);
    }

    /**
     * 监听
     */
    if (listen(listenfd, SOMAXCONN) < 0) {
        ERR_EXIT(listen);
    }

    /**
     * poll使用
     */
    struct pollfd pfd{};
    pfd.fd = listenfd;
    pfd.events = POLLIN;    //可读事件

    PollFdList pollfds;
    pollfds.emplace_back(pfd);

    int nready;

    struct sockaddr_in peeraddr{};
    socklen_t peerlen;
    int connfd;
    int idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);

    while (true) {
        nready = poll(pollfds.data(), pollfds.size(), -1);  //不设置超时
        if (nready == -1) {
            if (errno == EINTR) continue;
            ERR_EXIT(poll);
        }
        else if (nready == 0) continue;
        if (pollfds[0].revents & POLLIN) {  //监听套接字有可读事件
            peerlen = sizeof(peeraddr);
            connfd = accept4(listenfd, (struct sockaddr*)&peeraddr, &peerlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
            if (connfd == -1) {
                /**
                 * EMFILE 处理
                 * 创建一个空的文件描述符 先关闭 获得一个描述符名额
                 * 再拿到一个socket连接的文件描述符 随后立即关闭
                 * 最后再创建一个空的文件描述符以备用
                 */
                if (errno == EMFILE) {
                    close(idlefd);
                    idlefd = accept(listenfd, nullptr, nullptr);
                    close(idlefd);

                    idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);
                    continue;
                } else {
                    ERR_EXIT(appcept4);
                }
            }

            pfd.fd = connfd;
            pfd.events = POLLIN;
            pfd.revents = 0;
            pollfds.emplace_back(pfd);
            nready--;

            /**
             * 连接成功
             */
            std::cout << "ip=" << inet_ntoa(peeraddr.sin_addr) <<
                "port=" << ntohs(peeraddr.sin_port) << std::endl;
            if (nready == 0) continue;
        }

//        std::cout << pollfds.size() << std::endl;
//        std::cout << nready << std::endl;

        for (auto iter = pollfds.begin()+1; iter != pollfds.end() && nready > 0; ++iter) {  //遍历已连接套接字
            if (iter->revents & POLLIN) {   //已连接套接字有可读事件
                nready--;
                connfd = iter->fd;
                char buf[BufLen] = {0};
                int ret = read(connfd, buf, BufLen);
                if (ret == -1) {
                    ERR_EXIT(read);
                }
                else if (ret == 0) {
                    std::cout << "client close" << std::endl;
                    iter = pollfds.erase(iter);
                    iter--;
                    close(connfd);
                    continue;
                }

                std::cout << buf << std::endl;
                write(connfd, buf, strlen(buf));
            }
        }
    }
    return EXIT_SUCCESS;
}