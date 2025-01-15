#include "thread_pool.h"
#include <iostream>
#include <ostream>

Thread_Pool* Thread_Pool::manager = nullptr;
std::mutex Thread_Pool::m_mutex;

Thread_Pool* Thread_Pool::instance() {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (!manager) {
        manager = new Thread_Pool();
    }
    return manager;
}

Thread_Pool::Thread_Pool(size_t num_threads) : stop_pool(false) {
    for (size_t i = 0; i < num_threads; ++i) {
        workers.emplace_back([this] { worker(); });
    }
}

Thread_Pool::~Thread_Pool() {
    stop();
}

void Thread_Pool::stop() {
    stop_pool = true;
    condition.notify_all(); // 唤醒所有线程

    // 等待所有线程完成
    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void Thread_Pool::worker() {
    while (true) {
        Task task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            // 等待任务或停止信号
            condition.wait(lock, [this] {
                return stop_pool || !task_queue.empty();
            });
            // 如果线程池已停止且任务队列为空，退出线程
            if (stop_pool && task_queue.empty()) {
                return;
            }
            // 获取最高优先级的任务
            task = std::move(task_queue.top());
            task_queue.pop();
        }
        try {
            task.func(); // 执行任务
        } catch (const std::exception& e) {
            // 捕获并处理任务中的异常
            std::cerr << "Task failed with exception: " << e.what() << std::endl;
        }
    }
}
