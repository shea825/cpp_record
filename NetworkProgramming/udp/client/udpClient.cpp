//
// Created by shea on 3/1/22.
//

#include "udpClient.h"

#include <memory>
#include <utility>

#define UNIQUE_PTR_MAXSIZE 102400
udpClient::udpClient(std::string ip, std::string port): IP_(std::move(ip)), Port_(std::move(port)) {
}

int udpClient::connect() {
    syncQueue = std::make_unique<SyncQueue<Data>>(UNIQUE_PTR_MAXSIZE);
    worker = std::thread([this]() {
        while (true) {
            auto data = syncQueue->take();
        }
    });
}

int udpClient::close() const {
    return 0;
}

void udpClient::info() const {

}

int udpClient::send(std::vector<u_char> data) {
    return 0;
}




