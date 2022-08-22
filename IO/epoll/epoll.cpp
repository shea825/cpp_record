
/** @file epoll.cpp
 *  @author shea
 *  @date 5:27 PM 8/21/22
 *  @plat CLion
 *  @brief epoll LT
 *  1. epoll_wait
 *  2. 处理监听套接字事件
 *      listenfd EPOLLIN事件到来
 *      connfd = accept(4)
 *      关注connfd的EPOLLIN事件
 *  3. 处理已连接套接字事件
 *      处理活跃套接字集合
 *      connfd EPOLLIN事件到来
 *      read(connfd)
 *      ret = write(connfd, buf, 10000)
 *      if (ret < 10000) {
 *          将未发完的数据添加到应用层缓冲区OutBuffer
 *          关注connfd的 EPOLLOUT事件
 *      }
 *      connfd EPOLLOUT事件到来
 *      取出应用层缓冲区中的数据发送 write(connfd)
 *      如果应用层缓冲区中的数据发送完毕，取消关注 EPOLLOUT事件
 *      返回 步骤1
 *   @note
 *   LT 高电平触发
 *   ET 边缘触发    低->高 or 高->低
 *
 *   EPOLLIN事件
 *   内核中的socket接收缓冲区 为空      低电平
 *   内核中的socket接受缓冲区 不为空    高电平
 *
 *   EPOLLOUT事件
 *   内核中的socket发送缓冲区 不满      高电平
 *   内核中的socket发送缓冲区 满        低电平
 *
 */

#include <csignal>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define ERR_EXIT( FUNC ) \
    std::cerr << std::strerror(errno) << #FUNC << std::endl; \
    return EXIT_FAILURE

using EventList = std::vector<struct epoll_event>;

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
    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        ERR_EXIT(bind);
    }

    /**
     * 监听
     */
    if (listen(listenfd, SOMAXCONN) < 0) {
        ERR_EXIT(listen);
    }

    /**
     * epoll使用
     */
    std::vector<int> clients;
    int epollfd = epoll_create1(O_CLOEXEC);
    struct epoll_event event{};
    event.events = EPOLLIN; //可读事件  默认LT模式触发 可指定为边缘触发 EPOLLET
    event.data.fd = listenfd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event);    //添加到epollfd并关注

    EventList events(16);
    int nready;

    struct sockaddr_in peeraddr{};
    socklen_t peerlen;
    int connfd;
    int idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);

    while (true) {
        /**
         * 套接字所对应的事件数组@a events.data() 仅作为输出参数
         */
        nready = epoll_wait(epollfd, events.data(), static_cast<int>(events.size()), -1);  //不设置超时
        if (nready == -1) {
            if (errno == EINTR) continue;
            ERR_EXIT(poll);
        } else if (nready == 0) continue;
        if (nready == events.size()) {
            events.resize(events.size() * 2);
        }
        for (int i = 0; i < nready; ++i) {
            if (events.at(i).data.fd == listenfd) {
                peerlen = sizeof(peeraddr);
                connfd = accept4(listenfd, (struct sockaddr *) &peeraddr, &peerlen,
                                 SOCK_NONBLOCK | SOCK_CLOEXEC);
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
                /**
                 * 连接成功
                 */
                std::cout << "ip=" << inet_ntoa(peeraddr.sin_addr) <<
                          "port=" << ntohs(peeraddr.sin_port) << std::endl;

                clients.emplace_back(connfd);

                event.data.fd = connfd;
                event.events = EPOLLIN;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event);
            } else if (events.at(i).events & EPOLLIN) {  //监听套接字有可读事件
                connfd = events.at(i).data.fd;
                if (connfd < 0) continue;
                char buf[BufLen] = {0};

                int ret = read(connfd, buf, BufLen);
                if (ret == -1) {
                    ERR_EXIT(read);
                } else if (ret == 0) {
                    std::cout << "client close" << std::endl;
                    close(connfd);
                    event = events.at(i);
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, connfd, &event);  //从epollfd中删除并取消关注
                    clients.erase(std::remove(clients.begin(), clients.end(), connfd), clients.end());
                    continue;
                }
                std::cout << buf << std::endl;
                write(connfd, buf, strlen(buf));
            }
        }

    }
    return EXIT_SUCCESS;
}