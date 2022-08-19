
/** @file UringFile.h
 *  @author shea
 *  @date 11:31 AM 4/10/22
 *  @plat CLion
 *  @brief this is a simple file lib based on liburing
 */

#pragma once

#include <liburing.h>
#include <map>
#include <vector>
#include <string>

using files = std::map<std::string, int>;//file path

struct io_data {
    bool is_read;
    off_t first_offset, offset;
    size_t first_len;
    size_t file_size;
    std::vector<iovec> iovs;
};

class UringFile {
private:
    files files_;
    int QD_;
    long BS_;
    struct io_uring ring_{};
//    void queue_prep(struct io_data *data);
//    int queue_read(off_t size, off_t offset);
//    void queue_write(struct io_data *data);
public:
    explicit UringFile(int QUEUE_DEPTH = 2, long BLOCK_SZ = 64*1024);
    ~UringFile();

    void get_status() const;
    int get_fd(const char *file_path) const;
    int init(files file_map);
    int read_small_file(const char *file_path);
    int to_buffer(int fd, char* buf, size_t bufLen);
    int close_file(const char *file_path);
    int copy_file(off_t insize);
    size_t get_file_size(int fd);

};
