
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

    auto hc = std::thread::hardware_concurrency();
    std::cout << "Starting thread pool of " << hc << std::endl;
    thread_pool pool(hc);

    for(int i = 0; i < 100; ++i)
    {
        //std::function<int()> f;
        pool.schedule(&func);
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
    pool.stop();
}