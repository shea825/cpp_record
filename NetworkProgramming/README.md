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