
/** @file test_timer.cpp
 *  @author shea
 *  @date 6:41 PM 5/8/22
 *  @plat CLion
 *  @brief this is a 
 */

#include <iostream>
#include "../src/UringNet.h"

int main() {
    UringNet uringNet = UringNet();
    uringNet.init();
    auto server_fd = uringNet.setup_listen(8000);
    uringNet.add_accept_request(server_fd);
    uringNet.server(server_fd, [](std::string msg) {
        std::cout << msg << std::endl;
    });
}