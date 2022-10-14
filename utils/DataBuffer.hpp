//
// Created by shea on 10/8/22.
//

#pragma once

#include <utility>
#include <vector>
#include <cstring>
#include <iostream>
#include <netinet/in.h>

class ReadDataBuffer {
private:

    std::vector<unsigned char> data = {};

    size_t requirements = sizeof(int);

    bool length_bytes_inserted = false;

public:

    size_t todo() const {
        return requirements;
    }

    void insert(const char *buffer, int size) {
        size_t current_size = data.size();
        size_t new_size = current_size + size;
        data.resize(new_size);
        memcpy(data.data() + current_size, buffer, size);
        if (!length_bytes_inserted && new_size >= sizeof(int)) {
            requirements = ntohl(*(int *)data.data());

            requirements = requirements - (new_size - sizeof(int));
            length_bytes_inserted = true;
            data.erase(data.begin(), data.begin() + sizeof(int));
        } else {
            requirements = requirements - size;
        }
    }

    const std::vector<unsigned char> &get() const {
        return data;
    }

    std::vector<unsigned char> &&get() {
        return std::move(data);
    }

    void reset() {
        data.clear();
        requirements = sizeof(int);
        length_bytes_inserted = false;
    }
};

class SendDataBuffer {
private:

    std::vector<unsigned char> data = {};

    size_t left_over = 0;


public:



    SendDataBuffer(SendDataBuffer &&o) noexcept {
        this->data = std::move(o.data);
        this->left_over = o.left_over;
        o.left_over = 0;
    }

    explicit SendDataBuffer(std::vector<unsigned char> &&buffer) {
        data = std::move(buffer);
        auto size = data.size();
        auto network_size = htonl(size);
        std::vector<unsigned char> network_size_char(sizeof(network_size));
        memcpy(network_size_char.data(), &network_size, sizeof(network_size));
        data.insert(data.begin(), network_size_char.begin(),  network_size_char.end());
        left_over = data.size();
    }

    bool todo(size_t *size, const unsigned char **buffer) const {
        *buffer = data.data() + (data.size() - left_over);
        *size = left_over;
        return left_over != 0;
    }

    void remove(ssize_t size) {
        left_over -= size;
    }

    std::vector<unsigned char> value() const {
        return {data.begin() + sizeof(int), data.end()};
    }

    void rewind() {
        this->left_over = data.size();
    }

    size_t size() const {
        if (length_bytes_inserted)  {
            return data.size() - sizeof(int);
        }
        throw std::runtime_error("illegal buffer state, read not finished");
    }
};

