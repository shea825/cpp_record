
/** @file UringFile.cpp
 *  @author shea
 *  @date 10:54 AM 4/10/22
 *  @plat CLion
 *  @brief file interface based on io_uring
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cerrno>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <memory>
#include <utility>
#include <fcntl.h>
#include <unistd.h>
#include "UringFile.h"

UringFile::UringFile(int QUEUE_DEPTH, long BLOCK_SZ) {
    this->QD_ = QUEUE_DEPTH;
    this->BS_ = BLOCK_SZ;
}

int UringFile::init(files file_map) {
    int ret;
    this->files_ = std::move(file_map);
    ret = io_uring_queue_init(QD_, &ring_, 0);
    if( ret < 0) {
        fprintf(stderr, "queue_init: %s\n", strerror(-ret));
        return -1;
    }
    return 0;
}

size_t UringFile::get_file_size(int fd) {
    struct stat st{};

    if (fstat(fd, &st) < 0 )
        return -1;
    if(S_ISREG(st.st_mode)) {
        return st.st_size;
    } else if (S_ISBLK(st.st_mode)) {
        unsigned long bytes;

        if (ioctl(fd, BLKGETSIZE64, &bytes) != 0) {
            return -1;
        }
        return bytes;
    }
    return -1;
}

UringFile::~UringFile() {
    int to_close_fd;

    for (auto &file: files_) {
        to_close_fd = file.second;
        if (to_close_fd) {
            close(to_close_fd);
        }
    }
    io_uring_queue_exit(&ring_);
}

void UringFile::get_status() const {
    printf("QUEUE_DEPTH: %d\nBLOCK_SZ: %ld\n", QD_, BS_);
}

//file size <= BS
int UringFile::read_small_file(const char *file_path) {
    int file_fd = open(file_path, O_RDONLY);
    if (file_fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }
    auto file_size = get_file_size(file_fd);
    if (file_size > BS_) {
        perror("file size too big\n");
        return EXIT_FAILURE;
    }

    if (!files_.count(file_path)) {
        files_.emplace(file_path,file_fd);
    }
    auto *data_ptr = new io_data;

    auto buff = (char *)malloc(file_size);
    if (!buff) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return EXIT_FAILURE;
    }

    data_ptr->is_read = true;
    data_ptr->file_size = file_size;
    struct iovec iov{buff, file_size};

    data_ptr->iovs.emplace_back(iov);

    /* Get an SQE */
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring_);
    /* Setup a readv operation */
    io_uring_prep_readv(sqe, file_fd, data_ptr->iovs.data(), 1, 0);
    /* Set user data */
    io_uring_sqe_set_data(sqe, data_ptr);
    /* Finally, submit the request */
    io_uring_submit(&ring_);

    return 0;
}

int UringFile::to_buffer(int fd, char *buf, size_t buf_len) {
    struct io_uring_cqe *cqe;
    int ret = io_uring_wait_cqe(&ring_, &cqe);
    if (ret < 0) {
        perror("io_uring_wait_cqe");
        return EXIT_FAILURE;
    }
    if (cqe->res < 0) {
        fprintf(stderr, "Async readv failed.\n");
        return EXIT_FAILURE;
    }
    auto data_ptr = (io_data *)io_uring_cqe_get_data(cqe);
    auto buf_copy = buf;
    off_t read_len = 0;
    for (auto &iov: data_ptr->iovs) {
        if (buf_len < read_len + iov.iov_len) {
            break;
        }
        printf("%zu\n",iov.iov_len);
        memcpy(buf_copy, iov.iov_base, iov.iov_len);
        buf_copy += iov.iov_len;
        read_len += iov.iov_len;
    }
    io_uring_cqe_seen(&ring_, cqe);
    return EXIT_SUCCESS;
}

int UringFile::get_fd(const char *file_path) const {
    return files_.at(file_path);
}

int UringFile::close_file(const char *file_path) {
    if (files_.count(file_path)) {
        auto to_close_fd =  files_.at(file_path);
        close(to_close_fd);
        files_.erase(file_path);
        return EXIT_SUCCESS;
    } else {
        perror("do not open this file\n");
        return EXIT_FAILURE;
    }
}
