## 性能指标
* 带宽bandwidth    千兆以太网理论最大带宽117MB/s
* 吞吐量throughput
* 延迟latency
* 资源使用率payload  
* 额外开销overhead

## 常见并发服务器方案
* 循环式iterative
如果使用长连接，只能同时处理一个客户端
```text
socket(); bind(); listen() --> while{
  accept() --> read() 
  --> decode(); compute(); encode() 
  --> write() --> close()
  }
```
* 并发式
```text
socket(); bind(); listen() --> while{
  accept() --> fork() --> close()
  }
//子进程
while{
    read() -->
    decode(); compute(); encode() -->
    write()
} --> close()

```
  
* 预先创建线程
```text
socket(); bind(); listen() --> fork()
                           --> fork()
                           --> fork()
```

* 反应式reactor
    * 并发处理多个请求，实际上是在一个线程中完成的，无法充分利用多核CPU
    * 不适合执行时间较长的服务
```text
select()/poll/epoll
accept() --> dispatch -->
    read() -->
    decode(); compute(); encode() -->
    write()
```

* reactor + thread per request

* reactor + worker thread

* reactor + thread pool
    * 适用于计算密集型的任务
```text
select()/poll/epoll
accept() --> dispatch --> 
    read() --> thread pool --> one thread --> {
        decode(); compute(); encode()
    }
    --> write()
```
* multiple reactors
    * 能适应更大的突发I/O
    * one loop per thread
    
* multiple reactors + thread pool
    * 既适用于计算密集型的任务，也能适应更大的突发I/O
    
* proactor模式
    * 基于异步I/O，理论上比reactor效率要高
    * 异步I/O能让I/O操作与计算重叠，充分利用DMA特性
    
## 线程分类
* I/O线程
* 计算线程
* 第三方库所用线程，比如logging和数据库

## Tcp的三个半事件
* 连接建立
  * 服务器accept被动接受连接
  * 客户端connect主动发起连接
  
* 连接断开
  * 主动断开close shutdown
  * 被动断开read返回0
  
* 消息到达
  * 文件描述符可读
  
* 消息发送完毕
  * 对于低流量的服务，可不必关心这个事件;这里的发送完毕是指数据写入操作系统缓冲区，
    将由TCP协议栈负责数据的发送与重传，不代表对方已经接收到数据
    
## EventLoop
* one loop per thread意思是说每个线程最多只能有一个EventLoop对象
* EventLoop对象构造的时候，会检查当前线程是否已经创建了其他EventLoop对象，如果已创建，终止程序
* EventLoop构造函数会记住本对象所属线程 `threadId_`
* 创建了EventLoop对象的线程称为I/O线程，其功能是运行事件循环 `EventLoop::loop`

## Timer计时器函数选择
* sleep/alarm/usleep 在实现时可能用到了信号 SIGALRM，在多线程程序中处理信号是个相当麻烦的事情，应当尽量避免
* nanosleep和clock_nanosleep是线程安全的，但是在非阻塞网络编程中，绝对不能用让线程挂起的方式来等待一段时间，程序会失去响应。
  正确的做法是注册一个时间回调函数
  
* getitimer和timer_create也是用信号来deliver超时
* timer_create可以指定信号的接收方是进程还是线程，算是一个进步，不过在信号处理函数能做的事情实在很受限
* timerfd_create把时间变成了一个文件描述符，该“文件”在定时器超时的那一刻变得可读，这样就能很方便地融入到select/poll框架中，
  用统一的方式来处理IO事件和超时事件，这也正是Reactor模式的长处