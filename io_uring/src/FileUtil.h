
/** @file FileUtil.h
 *  @author shea
 *  @date 10:22 AM 4/10/22
 *  @plat CLion
 *  @brief this is a 
 */

#pragma once

#include <string>
#include "UringFile.h"

// read small file < 64KB
class ReadSmallFile {
public:
    explicit ReadSmallFile(const char *filename);
    ~ReadSmallFile();

    // return errno
    int readToString(int maxSize,
                     std::string &content,
                     int64_t* fileSize,
                     int64_t* modifyTime,
                     int64_t* createTime);

    int readToBuffer(int* size);

    const char* buffer() const { return buf_; }

    static const int kBufferSize = 64*1024;

    //noncopyable
    ReadSmallFile(ReadSmallFile&) = delete;
    ReadSmallFile& operator=(ReadSmallFile&) = delete;

private:
    int fd_;
    int err_;
    char buf_[kBufferSize]{};
    UringFile uringFile;
};

// read the file content, returns errno if error happens.
int readFile(std::string filename,
             int maxSize,
             std::string &content,
             int64_t* fileSize = nullptr,
             int64_t* modifyTime = nullptr,
             int64_t* createTime = nullptr);

class AppendFile {
public:
    explicit AppendFile(std::string filename);

    ~AppendFile();

    void append(const char *logline, const size_t len);

    void flush();

    off_t writtenBytes() const { return writtenBytes_; }

private:

    size_t write(const char *logline, size_t len);

    FILE *fp_;
    char buffer_[64 * 1024];
    off_t writtenBytes_;
};