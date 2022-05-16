
/** @file FileUtil.cpp
 *  @author shea
 *  @date 10:19 AM 4/10/22
 *  @plat CLion
 *  @brief this is a 
 */

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "FileUtil.h"

ReadSmallFile::ReadSmallFile(const char *filename) : err_(0) {
    buf_[0] = '\0';
    uringFile.init({});
    uringFile.read_small_file(filename);
    fd_ = uringFile.get_fd(filename);
    if (fd_ < 0) {
        err_ = errno;
    }
}

ReadSmallFile::~ReadSmallFile()
{
    if (fd_ >= 0)
    {
        close(fd_); // FIXME: check EINTR
    }
}

int ReadSmallFile::readToString(int maxSize,
                                std::string &content,
                                int64_t *fileSize,
                                int64_t *modifyTime,
                                int64_t *assessTime) {
    static_assert(sizeof(off_t) == 8);
    int err = err_;
    if (fd_ >= 0) {
        content.clear();
        if (fileSize) {
            struct stat st{};
            if (fstat(fd_, &st) == 0) {
                if (S_ISREG(st.st_mode)) {
                    *fileSize = uringFile.get_file_size(fd_);
                    content.reserve(std::min(static_cast<int64_t>(maxSize), *fileSize));
                } else if (S_ISDIR(st.st_mode)) {
                    err = EISDIR;
                }
                if (modifyTime) {
                    *modifyTime = st.st_mtime;
                }
                if (assessTime) {
                    *assessTime = st.st_atime;
                }
            } else {
                err = errno;
            }
        }
        if (content.size() < static_cast<int64_t>(maxSize)) {
            size_t toRead = std::min(static_cast<int64_t>(maxSize) - content.size(), sizeof(buf_));
//            ssize_t n = read(fd_, buf_, toRead);
            if (uringFile.to_buffer(fd_, buf_, toRead) == EXIT_SUCCESS) {
                content.append(buf_, *fileSize);
            }
        }
    }
    return err;
}

int ReadSmallFile::readToBuffer(int *size) {
    int err = err_;
    if (fd_ >= 0)
    {
        ssize_t n = uringFile.to_buffer(fd_, buf_, sizeof(buf_)-1);
        if (n >= 0)
        {
            if (size)
            {
                *size = static_cast<int>(n);
            }
            buf_[n] = '\0';
        }
        else
        {
            err = errno;
        }
    }
    return err;
}


int readFile(std::string filename, int maxSize, std::string &content, int64_t *fileSize, int64_t *modifyTime,
             int64_t *createTime) {
    ReadSmallFile file(filename.c_str());
    return file.readToString(maxSize, content, fileSize, modifyTime, createTime);
}
