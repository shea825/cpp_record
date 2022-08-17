
/** @file test_FileUtil.cpp
 *  @author shea
 *  @date 7:34 PM 5/6/22
 *  @plat CLion
 *  @brief this is a 
 */
#include "../src/FileUtil.h"


int main() {
    const char * test = "../../io_uring/test/testSample.txt";
    ReadSmallFile readSmallFile(test);
    std::string content;
    int64_t file_size, mtime, atime;
    readSmallFile.readToString(100, content, &file_size, &mtime, &atime);
    printf("content: %s\n"
           "file size: %ld\n"
           "motify time: %ld\n"
           "assess time: %ld\n",content.c_str(),file_size,mtime,atime);
}