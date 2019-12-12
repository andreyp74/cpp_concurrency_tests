#include "queue_on_atomic.hpp"

int main()
{
    queue_on_atomic q;

    std::thread t1(&queue_on_atomic::populate, &q);

    std::thread t2(&queue_on_atomic::consume, &q);
    std::thread t3(&queue_on_atomic::consume, &q);
    std::thread t4(&queue_on_atomic::consume, &q);
    std::thread t5(&queue_on_atomic::consume, &q);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}