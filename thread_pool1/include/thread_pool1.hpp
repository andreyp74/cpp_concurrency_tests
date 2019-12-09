#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <condition_variable>
#include <queue>
#include <iostream>
#include <atomic>

class thread_pool
{
    std::vector<std::thread> pool;
    std::mutex mtx;
    std::condition_variable cond;
    std::queue<std::function<int()>> q;
    int thread_pool_size;
    std::atomic<bool> is_active = true;

    public:

        thread_pool(int thread_pool_size) : thread_pool_size(thread_pool_size)
        {
            for(int i = 0; i < thread_pool_size; ++i)
                pool.emplace_back(std::thread(&thread_pool::thread_func, this));
        }

        ~thread_pool()
        {
            for(int i = 0; i < thread_pool_size; ++i)
                pool[i].join();
        }

        void schedule(std::function<int()>&& task)
        {
            std::unique_lock<std::mutex> lock(mtx);

            q.emplace(task);
            cond.notify_one();
        }

        void stop()
        {
            is_active = false;
            cond.notify_all();
        }

        void thread_func()
        {
            while(is_active)
            {
                std::unique_lock<std::mutex> lock(mtx);
                if (q.empty())
                    cond.wait(lock);

                auto& task = q.front();
                q.pop();

                lock.unlock();

                auto result = task();
                std::cout << "task finished with code: " << result << std::endl;
            }
        }
};