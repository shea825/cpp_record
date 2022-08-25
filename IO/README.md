## select/poll/epoll 对比
* select 
本质上是通过设置或检查存放fd标志位的数据结构来进行下一步处理，缺点是
    1. 单个进程可监视的fd数量被限制 `FD_SETSIZE`
    2. 需要维护一个用来存放大量fd的数据结构，使得用户空间和内核空间在传递该结构
  时复制开销大
    3. 对socket进行扫描时是线性扫描 `FD_ISSET`
* poll 
本质上和select没有区别，它将用户传入的数据拷贝到内核空间，然后查询每个
fd对应的设备状态，如果设备就绪则在设备等待队列中加入一项并继续遍历，如果遍历完所
有fd后没有发现就绪设备，则挂起当前进程，直到设备就绪或者主动超时，被唤醒后它又要
再次遍历fd。这个过程经历了多次无谓的遍历。
它没有最大连接数的限制，原因是它是基于链表来存储的，但同样有缺点
    1. 大量的fd数组被整体复制于用户态和内核地址空间之间，而不管这样的复制是不是
  有意义的
    2. 水平触发问题：如果报告了fd后没有被处理，那么下次poll时会再次报告该fd
* epoll
epoll使用mmap减少复制开销
epoll使用“事件”的就绪通知方式，通过epoll_ctl注册fd，一旦该fd就绪，内核就会采
用类似callback的回调机制来激活该fd，epoll_wait便可以收到通知
对socket底层用红黑树和双向链表，效率高