#include <cinttypes>
#include <numeric>
#include <set>
#include <string>
#include <cstring>
#include <tuple>
#include <vector>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
#include <pthread.h>
#include <unistd.h>
#include "RingBuffer.h"
#include "UsbInfo.h"

pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  fifo_nonzero;

class UsbMonitorDevice {
public:
    explicit UsbMonitorDevice(char* name){
        mDev_name = name;
    }
    ~UsbMonitorDevice(){
        epoll_ctl(mEpollfd, EPOLL_CTL_DEL, mFd, &mEpev);
        close(mEpollfd);
        close(mFd);
    }

    int InitSetup(){
        //open "/proc/usb_monitor"
        mFd = open(mDev_name, O_RDWR);
        if (mFd == -1) {
            printf("open %s fail, %s\n",mDev_name,strerror(errno));
            return errno;
        }
        //epoll
        mEpollfd = epoll_create(MAX_EPOLL_EVENTS);
        if (mEpollfd == -1) {
            printf("epoll_create failed errno = %d ", errno);
            return errno;
        }
        printf("epoll_create ok epollfd= %d \n", mEpollfd);

        //add fd for epoll
        memset(&mEpev, 0, sizeof(mEpev));
        mEpev.data.fd = mFd;
        mEpev.events = EPOLLIN;
        if (epoll_ctl(mEpollfd, EPOLL_CTL_ADD, mFd, &mEpev) < 0) {
            printf("epoll_ctl failed, errno = %d \n", errno);
            return errno;
        }
        return 0;
    }

    int getFd() const { return mFd; };
    int getepollfd() const { return mEpollfd; };
    char* getBuffer() { return mBuf; };

    DataInfo& GetFristDataInfo(){
        return mRingBuffer.Get(0);
    }
    void PPopFrontDatainfo(){
        mRingBuffer.PopFront();
    }

    void PopBackDatainfo(){
        mRingBuffer.PopBack();
    }

    DataInfo& GetBackDataInfo(){
        return mRingBuffer.Back();
    }

    void AppendDatainfo(DataInfo& info){
        mRingBuffer.Append(info);
    }

    size_t GetFifoSize(){
        return mRingBuffer.GetSize();
    }

    void FifoReset(size_t capacity) {
        mRingBuffer.Reset(capacity);
    }

    bool FifoIsEmpty() {
        return mRingBuffer.IsEmpty();
    }

private:
    int mFd{}; //"/proc/suspend_monitor"
    int mEpollfd{};
    struct epoll_event mEpev{};
    char *mDev_name;
    char mBuf[128]{};
    RingBuffer<DataInfo> mRingBuffer;
};

static void * DoUsbMonitor(void *arg){
    int ret;
    //static int index = 0;
    ssize_t leng = 0, i = 0;
    struct epoll_event epev{};
    DataInfo deviceinfo{};
    UsbMonitorDevice* device = (UsbMonitorDevice*)arg;
    char* buf = device->getBuffer();
    device->FifoReset(BUFFER_SIZE);

    while(true){
        printf("usb_monitor epoll_wait... \n");
        ret = epoll_wait(device->getepollfd(), &epev, MAX_EPOLL_EVENTS, -1);
        if (ret == -1 && errno != EINTR) {
            printf("usb_monitor epoll_wait failed; errno=%d\n", errno);
            return (void*)-1;
        }
        leng  = read(device->getFd(), buf, KERNEL_DATA_LENG); //MAX 128 Byte
        // 读取文件函数调用 驱动中的 usb_monitor_read
        if ( leng > 0 ){
            printf("read length is %zd\n",leng);
            //8 字节的 kernel time
            for (i = 0; i < 8; i++){
                data_info.kernel_time[i] = buf[i];
                printf("kernel_time[%zd] = 0x%x \n", i, data_info.kernel_time[i]);
            }
            // 记录插拔状态
            data_info.status = buf[8];
            // 拷贝USB名称
            memcpy(data_info.name,buf+9,leng-9);

            if(data_info.status==1){
                printf("USB Device %s -> plug In \n",data_info.name);
            }else{
                printf("USB Device %s -> plug Out \n",data_info.name);
            }
            printf("\n");
        }
    }
}

int main(){
    int ret;
    pthread_t ptd;
    //check device
    UsbMonitorDevice* monitorDevice = new UsbMonitorDevice((char*)DEV_NAME);
    if ( monitorDevice->InitSetup() != 0){
        printf("UsbMonitorDevice::InitSetup fail \n");
        return -1;
    }
    printf("UsbMonitorDevice::InitSetup OK \n");

    DoUsbMonitor((void*)monitorDevice);

    pthread_mutex_destroy(&data_mutex);
    //not call here
    return 0;
}
