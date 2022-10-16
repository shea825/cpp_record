## 一个线程通知一个等待中线程的方法
1. pipe
    * 单向的
2. socketpair
    * `fd[0] fd[1]`双向
3. eventfd
    * eventfd是一个比pipe更高效的线程间时间通知机制，
   一方面它比pipe少用一个文件描述符，节省了资源；
   另一方面eventfd的缓冲区管理也简单得多，全部buffer
   只有**定长8bytes**，不像pipe那样可能有不定长的真正buffer
4. condition
