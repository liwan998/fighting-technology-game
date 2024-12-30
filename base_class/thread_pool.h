#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include<thread>
#include<mutex>
#include<condition_variable>
#include<functional>
#include<vector>
#include<queue>

class Thread_Pool
{
public:
    static Thread_Pool* instance();
    void over_task();

    template<class F, class... Argc>
    void add_task(F&& f, Argc&&... args) {
        auto task = std::bind(std::forward<F>(f), std::forward<Argc>(args)...);
        std::unique_lock<std::mutex> lock(task_mutex);
        task_queue.emplace(std::move(task));
        lock.unlock();
        task_cv.notify_one();
    }

private:
    Thread_Pool(int num_threads);
    ~Thread_Pool();

private:
    static Thread_Pool* manager;

    std::vector<std::thread> thread_list;
    std::queue<std::function<void()>> task_queue;
    std::mutex task_mutex;
    std::condition_variable task_cv;
    bool stop = false;
};

#endif // THREAD_POOL_H
