//
// Created by shea on 8/25/22.
//

#pragma once

#include <thread>

class Thread {
public:
    Thread();
    virtual ~Thread();

    void Start();
    void Join();

private:
    static void* ThreadRoutine(void* arg);
    virtual void Run() = 0;
    pthread_t threadId_{};
};