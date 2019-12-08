
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "thread_pool1.hpp"

int func()
{
    return std::rand();
}

int main()
{
    std::srand(std::time(nullptr));

    thread_pool pool(10);

    for(int i = 0; i < 10000; ++i)
    {
        //std::function<int()> f;
        pool.schedule(&func);
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
    pool.stop();
}