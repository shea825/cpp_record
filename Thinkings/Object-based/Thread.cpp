//
// Created by shea on 8/26/22.
//

#include <iostream>
#include <unistd.h>
#include "Thread.h"

Thread_1::Thread_1(const std::function<void()> &threadFunc) : func_(threadFunc),
                                                          autoDelete_(false) {
  std::cout << "thread construct ..." << std::endl;
}

void Thread_1::Start() {
  pthread_create(&threadId_, nullptr, ThreadRoutine, this);
}

void Thread_1::Join() {
  pthread_join(threadId_, nullptr);
}

void *Thread_1::ThreadRoutine(void *arg) {
  auto *thread = static_cast<Thread_1 *>(arg);
  thread->Run();
  return nullptr;
}

void Thread_1::SetAutoDelete(bool autoDelete) {
  autoDelete_ = autoDelete;
}

void Thread_1::Run() {
  func_();
}

void ThreadFunc() {
  std::cout << "this is a ThreadFunc" << std::endl;
}

void ThreadFunc1(int count) {
  while (count--) {
    std::cout << "Thread_1 Run ... round" << count << std::endl;
    sleep(1);
  }
}

/**
 * 基于对象的编程思想
 * 具体类不继承抽象类，而是构造一个抽象类对象，然后定义回调函数（是具体类成员函数），
 * 通过抽象类相应的回调函数设置接口将实现的回调函数传递进去
 */

int main() {
//  Thread_1 t1(ThreadFunc);
  Thread_1 t2(std::bind(ThreadFunc1, 5));
  t2.Start();
  t2.Join();
  return EXIT_SUCCESS;
}