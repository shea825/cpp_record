
/** @file NetUtil.cpp
 *  @author shea
 *  @date 12:38 PM 5/10/22
 *  @plat CLion
 *  @brief this is a 
 */

#include <strings.h>
#include <cassert>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
#include "Socket.h"
#include "SocketOps.h"


InetAddress::InetAddress(uint16_t port, bool loopbackOnly, bool ipv6) {
    static_assert(offsetof(InetAddress, addr6_) == 0);
    static_assert(offsetof(InetAddress, addr_) == 0);
    if (ipv6) {
        bzero(&addr6_, sizeof addr6_);
        addr6_.sin6_family = AF_INET6;
        in6_addr ip = loopbackOnly ? in6addr_loopback : in6addr_any;
        addr6_.sin6_addr = ip;
        addr6_.sin6_port = htobe16(port);
    } else {
        bzero(&addr_, sizeof addr_);
        addr_.sin_family = AF_INET;
        in_addr_t ip = loopbackOnly ? INADDR_LOOPBACK : INADDR_ANY;
        addr_.sin_addr.s_addr = htobe32(ip);
        addr_.sin_port = htobe16(port);
    }
}

InetAddress::InetAddress(std::string ip, uint16_t port, bool ipv6) {
    if (ipv6) {
        bzero(&addr6_, sizeof addr6_);
        addr6_.sin6_family = AF_INET6;
        addr6_.sin6_port = htobe16(port);
    } else {
        bzero(&addr_, sizeof addr_);
        addr_.sin_family = AF_INET;
        addr_.sin_port = htobe16(port);
    }
}

void toIp(char *buf, size_t size,
          const struct sockaddr *addr) {
    if (addr->sa_family == AF_INET) {
        assert(size >= INET_ADDRSTRLEN);
        const struct sockaddr_in *addr4 =
                static_cast<const struct sockaddr_in *>(implicit_cast<const void *>(addr));
        ::inet_ntop(AF_INET, &addr4->sin_addr, buf, static_cast<socklen_t>(size));
    } else if (addr->sa_family == AF_INET6) {
        assert(size >= INET6_ADDRSTRLEN);
        const struct sockaddr_in6 *addr6 =
                static_cast<const struct sockaddr_in6 *>(implicit_cast<const void *>(addr));
        ::inet_ntop(AF_INET6, &addr6->sin6_addr, buf, static_cast<socklen_t>(size));
    }
}

std::string InetAddress::toIp() const {
    char buf[64] = "";
    ::toIp(buf, sizeof buf, getSockAddr());
    return buf;
}

void toIpPort(char *buf, size_t size,
              const struct sockaddr *addr) {
    toIp(buf, size, addr);
    size_t end = ::strlen(buf);
    const struct sockaddr_in *addr4 =
            static_cast<const struct sockaddr_in *>(implicit_cast<const void *>(addr));
    uint16_t port = be16toh(addr4->sin_port);
    assert(size > end);
    snprintf(buf + end, size - end, ":%u", port);
}

std::string InetAddress::toIpPort() const {
    char buf[64] = "";
    ::toIpPort(buf, sizeof buf, getSockAddr());
    return buf;
}

uint16_t InetAddress::toPort() const {
    return be16toh(portNetEndian());
}

uint32_t InetAddress::ipNetEndian() const {
    assert(family() == AF_INET);
    return addr_.sin_addr.s_addr;
}

static __thread char t_resolveBuffer[64 * 1024];

bool InetAddress::resolve(std::string hostname, InetAddress *result) {
    assert(result != nullptr);
    struct hostent hent{};
    struct hostent *he = nullptr;
    int herrno = 0;
    bzero(&hent, sizeof(hent));

    int ret = gethostbyname_r(hostname.c_str(), &hent, t_resolveBuffer, sizeof t_resolveBuffer, &he, &herrno);
    if (ret == 0 && he != nullptr) {
        assert(he->h_addrtype == AF_INET && he->h_length == sizeof(uint32_t));
        result->addr_.sin_addr = *reinterpret_cast<struct in_addr *>(he->h_addr);
        return true;
    } else {
        return false;
    }
}

int acceptOps(int sockfd, struct sockaddr_in6 *addr) {
    socklen_t addrlen = static_cast<socklen_t>(sizeof *addr);
#if VALGRIND || defined (NO_ACCEPT4)
    int connfd = ::accept(sockfd, sockaddr_cast(addr), &addrlen);
      setNonBlockAndCloseOnExec(connfd);
#else
    int connfd = ::accept4(sockfd, static_cast<struct sockaddr *>(implicit_cast<void *>(addr)),
                           &addrlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
#endif
    if (connfd < 0) {
        int savedErrno = errno;
        perror("Socket::accept");
        switch (savedErrno) {
            case EAGAIN:
            case ECONNABORTED:
            case EINTR:
            case EPROTO: // ???
            case EPERM:
            case EMFILE: // per-process lmit of open file desctiptor ???
// expected errors
                errno = savedErrno;
                break;
            case EBADF:
            case EFAULT:
            case EINVAL:
            case ENFILE:
            case ENOBUFS:
            case ENOMEM:
            case ENOTSOCK:
            case EOPNOTSUPP:
// unexpected errors
                perror("unexpected error of ::accept ");
                break;
            default:
                perror("unknown error of ::accept ");
                break;
        }
    }
    return connfd;
}