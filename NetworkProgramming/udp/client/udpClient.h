//
// Created by shea on 3/1/22.
//

#pragma once
#include <vector>
#include <string>
#include <thread>
#include <cstdlib>
#include "syncQueue.hpp"
using Data = std::vector<unsigned char>;
class udpClient {
public:
    explicit udpClient(std::string  ip = "127.0.0.1", std::string  port = "8888");
    int connect();
    int close() const;
    void info() const;
    int send(std::vector<u_char> data);
    int rev(std::vector<u_char> &data);
    ~udpClient() = default;
private:
    std::string IP_;
    std::string Port_;
    int cfd_{};
    std::thread worker;
    std::unique_ptr<SyncQueue<Data>> syncQueue;
};
