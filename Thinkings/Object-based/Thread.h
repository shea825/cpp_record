//
// Created by shea on 8/26/22.
//

#pragma once

#include <functional>
#include <pthread.h>

class Thread_1 {
public:
  using ThreadFunc = std::function<void ()>;
  explicit Thread_1(const ThreadFunc& threadFunc);

  void Start();
  void Join();

  void SetAutoDelete(bool autoDelete);

private:
  static void* ThreadRoutine(void* arg);
  void Run();
  ThreadFunc func_;
  pthread_t threadId_{};
  bool autoDelete_;
};

