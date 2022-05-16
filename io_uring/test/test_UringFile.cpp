
/** @file test.cpp
 *  @author shea
 *  @date 8:55 PM 4/8/22
 *  @plat CLion
 *  @brief this is a 
 */

#include <fcntl.h>
#include <iostream>
#include <cstring>
#include "../src/UringFile.h"

#define QD	2
#define BS	(16*1024)

int main() {
    UringFile uringFile;
//    auto infd = open("/home/shea/CLionProjects/cpp_record/io_uring/test/testSample.txt",
//                          O_RDONLY);
//    if (infd < 0) {
//        std::cerr << "open infile" << std::endl;
//        return 1;
//    }
//    auto outfd = open("/home/shea/CLionProjects/cpp_record/io_uring/test/testSampleCopy.txt",
//                            O_WRONLY | O_CREAT | O_TRUNC, 0644);
//    if (outfd < 0) {
//        std::cerr << "open outfile" << std::endl;
//        return 1;
//    }
//    if (uringFile.init(infd, outfd) == -1) {
//        return EXIT_FAILURE;
//    }
//    uringFile.get_status();
//    off_t insize = uringFile.get_file_size(infd);
//    if (insize == -1) {
//        return EXIT_FAILURE;
//    }
//    std::cout << insize << std::endl;
//    auto ret = uringFile.copy_file(insize);
    const char * test = "/home/shea/CLionProjects/cpp_record/io_uring/test/testSample.txt";
    uringFile.init({});
    uringFile.read_small_file(test);
    auto fd = uringFile.get_fd(test);
    char buf[50];
    memset(buf,0,50);
    uringFile.to_buffer(fd, buf, 50);
    printf("%s\n", buf);
}