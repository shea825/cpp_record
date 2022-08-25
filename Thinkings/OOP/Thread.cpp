//
// Created by shea on 8/25/22.
//


#include <iostream>
#include <unistd.h>
#include "Thread.h"

Thread::Thread() {
    std::cout << "thread construct ..." << std::endl;
}

void Thread::Start() {
    pthread_create(&threadId_, nullptr, ThreadRoutine, this);
}

void Thread::Join() {

}

void *Thread::ThreadRoutine(void *arg) {
    auto *thread = static_cast<Thread *>(arg);
    thread->Run();
    return nullptr;
}

Thread::~Thread() {
    std::cout << "thread destruct ..." << std::endl;
}


class TestThread : public Thread {
public:
    int count_;
    explicit TestThread(int count) :count_(count) {
        std::cout << "TestThread construct ..." << std::endl;
    }
    ~TestThread() override {
        std::cout << "TestThread destruct ..." << std::endl;
    }
    void Run() override {
        while (count_--) {
            std::cout << "TestThread Run ..." << std::endl;
            sleep(1);
        }
    }
};

int main() {
    TestThread t(5);
    t.Start();
    return EXIT_SUCCESS;
}
