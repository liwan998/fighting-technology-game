#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <future>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <stdexcept>

class Thread_Pool {
public:
    // 获取单例实例
    static Thread_Pool* instance();

    // 添加任务（支持优先级和返回值）
    template<class F, class... Args>
    auto add_task(int priority, F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;

    // 停止线程池
    void stop();

private:
    Thread_Pool(size_t num_threads = 4); // 构造函数
    ~Thread_Pool();

    // 禁用拷贝构造函数和赋值运算符
    Thread_Pool(const Thread_Pool&) = delete;
    Thread_Pool& operator=(const Thread_Pool&) = delete;

    // 任务结构体（包含优先级和可调用对象）
    struct Task {
        int priority;
        std::function<void()> func;

        // 重载 < 运算符，用于优先级队列
        bool operator<(const Task& other) const {
            return priority < other.priority; // 优先级越高，值越小
        }
    };

    // 工作线程函数
    void worker();

private:
    static Thread_Pool* manager; // 单例实例
    static std::mutex m_mutex;   // 单例锁

    std::vector<std::thread> workers;         // 工作线程
    std::priority_queue<Task> task_queue;     // 任务队列（按优先级排序）
    std::mutex queue_mutex;                   // 任务队列锁
    std::condition_variable condition;        // 条件变量
    std::atomic<bool> stop_pool;              // 线程池停止标志
};

// 添加任务的实现
template<class F, class... Args>
auto Thread_Pool::add_task(int priority, F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    // 将任务包装为 std::packaged_task，以支持返回值
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

    // 获取任务的 future
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        // 如果线程池已停止，抛出异常
        if (stop_pool) {
            throw std::runtime_error("线程池已停止");
        }
        // 将任务添加到队列
        task_queue.push({priority, [task]() { (*task)(); }});
    }
    // 通知一个等待的线程
    condition.notify_one();
    return res;
}

#endif // THREAD_POOL_H
