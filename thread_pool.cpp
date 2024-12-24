#include "thread_pool.h"

Thread_Pool* Thread_Pool::manager = nullptr;

Thread_Pool* Thread_Pool::instance()
{
    if (!manager) {
        manager = new Thread_Pool(4);
    }
    return manager;
}

void Thread_Pool::over_task()
{
    if(!task_queue.empty()){
        task_cv.notify_all();
        for (auto& t : thread_list) {
            t.join();
        }
    }
}


Thread_Pool::Thread_Pool(int num_threads)
{
    for (int i = 0; i < num_threads; i++) {
        thread_list.emplace_back([this] {
            while (true) {
                std::unique_lock<std::mutex> lock(task_mutex);
                task_cv.wait(lock, [this] {return !task_queue.empty() || stop; });
                if (stop && task_queue.empty()) {
                    return;
                }
                auto task = std::move(task_queue.front());
                task_queue.pop();
                lock.unlock();
                task();
            }
        });
    }
}

Thread_Pool::~Thread_Pool()
{
    {
        std::unique_lock<std::mutex> lock(task_mutex);
        stop = true;
    }
    task_cv.notify_all();
    for (auto& t : thread_list) {
        t.join();
    }
}

