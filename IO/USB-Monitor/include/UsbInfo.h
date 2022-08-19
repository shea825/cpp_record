#pragma once

#include <linux/types.h>
#include <linux/ioctl.h>
#include <cstddef>


#define DEV_NAME "/proc/usb_monitor"


#define MAX_EPOLL_EVENTS         1
#define KERNEL_DATA_LENG        128
#define MONITOR_DISABLE       0x00
#define MONITOR_ENABLE        0xff

size_t BUFFER_SIZE = 1024;

// 定义所用信息的结构体
struct DataInfo{
    unsigned char kernel_time[8];       //8 Byte
    unsigned char status;               //1 Byte
    char name[128];                         //unknow
}data_info;

