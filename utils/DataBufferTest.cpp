//
// Created by shea on 10/8/22.
//

#include <cctype>
#include <cstdint>
#include <netinet/in.h>
#include <iostream>

int main() {
    uint32_t i = 32;
    std::cout << be32toh(i) << std::endl << ntohl(i) << std::endl;
}

