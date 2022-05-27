
/** @file Socket.h
 *  @author shea
 *  @date 6:45 PM 5/8/22
 *  @plat CLion
 *  @brief this is a 
 */

#pragma once
#include <netinet/in.h>
#include <string>
struct tcp_info;//in <netinet/tcp.h>

class InetAddress;

struct non_copyable {
    non_copyable() = default;

    non_copyable(non_copyable&&) = default;
    non_copyable& operator=(non_copyable&&) = default;

    // you shall not copy
    non_copyable(const non_copyable&) = delete;
    non_copyable& operator=(const non_copyable&) = delete;
};

class Socket : non_copyable {
private:
    const int sockfd_;
public:
    explicit Socket(const int sockfd) : sockfd_(sockfd) {};
    ~Socket();

    int fd() const { return sockfd_; }

    // return true if success.
    bool getTcpInfo(struct tcp_info *) const;

    bool getTcpInfoString(char *buf, int len) const;

    /// abort if address in use
    void bindAddress(const InetAddress &localaddr);

    /// abort if address in use
    void listen();

    /// On success, returns a non-negative integer that is
    /// a descriptor for the accepted socket, which has been
    /// set to non-blocking and close-on-exec. *peeraddr is assigned.
    /// On error, -1 is returned, and *peeraddr is untouched.
    int accept(InetAddress *peeraddr);

    void shutdownWrite();

    ///
    /// Enable/disable TCP_NODELAY (disable/enable Nagle's algorithm).
    ///
    void setTcpNoDelay(bool on);

    ///
    /// Enable/disable SO_REUSEADDR
    ///
    void setReuseAddr(bool on);

    ///
    /// Enable/disable SO_REUSEPORT
    ///
    void setReusePort(bool on);

    ///
    /// Enable/disable SO_KEEPALIVE
    ///
    void setKeepAlive(bool on);

};
