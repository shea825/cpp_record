//
// Created by shea on 10/9/22.
//

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <chrono>

#define DATALEN 10000

int main() {
    char data[DATALEN] = {0};
    for (int i = 0; i < DATALEN; ++i) {
        data[i] = i % 128;
    }
    const char kCRLF[] = "op";  //o 111     p 112

    //std::search
    auto now = std::chrono::system_clock::now(); //for time
    const char *searchRet = std::search(data, data + DATALEN - 1, kCRLF, kCRLF + 2);
    auto searchCost = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - now);
    assert(searchRet == data + 111);
    //memmem
    now = std::chrono::system_clock::now(); //for time
    const char* memmemRet = (char *)memmem(data, DATALEN, kCRLF, 2);
    auto memmemCost = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - now);
    assert(searchRet == data + 111);

    std::cout << "std::search cost " << searchCost.count() << std::endl <<
    "memmem cost " << memmemCost.count() << std::endl;
}