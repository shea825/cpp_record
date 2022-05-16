//
// Created by shea on 3/1/22.
//

#pragma once

#include <list>
#include <mutex>
#include <condition_variable>
#include <iostream>


template<typename T>
class SyncQueue {
public:
    explicit SyncQueue(int maxSize) : m_maxSize(maxSize) {
    }

    void put(const T &x) {
        std::lock_guard<std::mutex> locker(m_mutex);

        while (isFull()) {
            std::cout << "the blocking queue is full,waiting..." << std::endl;
            m_notFull.wait(m_mutex);
        }
        m_queue.push_back(x);
        m_notEmpty.notify_one();
    }

    T take() {
        std::lock_guard<std::mutex> locker(m_mutex);

        while (isEmpty()) {
//            std::cout << "the blocking queue is empty,wating..." << std::endl;
            m_notEmpty.wait(m_mutex);
            if (closed) {
                return {};
            }
        }

        auto x = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
        return x;
    }

    int size() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size();
    }

    void close() {
        closed = true;
        m_notEmpty.notify_one();
    }

private:
    bool isFull() const {
        return m_queue.size() == m_maxSize;
    }

    bool isEmpty() const {
        return m_queue.empty();
    }


private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable_any m_notEmpty;
    std::condition_variable_any m_notFull;
    int m_maxSize;
    bool closed = false;
};