
#include <thread>
#include <mutex>
#include <iostream>

#include "mutex_on_atomic.hpp"

int g_i = 0;
mutex_on_atomic mtx_on_atomic;
std::mutex mtx;

void test_mutex()
{
    std::lock_guard<std::mutex> lock(mtx);
    ++g_i;
 
    std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
}

void test_mutex_on_atomic()
{
    std::lock_guard<mutex_on_atomic> lock(mtx_on_atomic);
    ++g_i;
 
    std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
}

void test1()
{
    std::cout << "main: " << g_i << '\n';

    std::thread t1(test_mutex_on_atomic);
    std::thread t2(test_mutex_on_atomic);
    std::thread t3(test_mutex_on_atomic);
    std::thread t4(test_mutex_on_atomic);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "main: " << g_i << '\n';
}

int data[10];

void write_array()
{
    //std::lock_guard<mutex_on_atomic> lock(mtx_on_atomic);
    for (int i = 0; i < 10; i++)
        data[i] = i;
}

void read_array()
{
    //std::lock_guard<mutex_on_atomic> lock(mtx_on_atomic);
    for (int i = 0; i < 10; i++)
        std::cout << data[i];
    std::cout << '\n';
}

void test2()
{
    std::thread t1(write_array);
    std::thread t2(read_array);

    t1.join();
    t2.join();
}

int data2[10];
int g_index = 0;

void write_index()
{
    //std::lock_guard<mutex_on_atomic> lock(mtx_on_atomic);

    data2[g_index] = g_index;
    ++g_index;
}

void read_all()
{
    //std::lock_guard<mutex_on_atomic> lock(mtx_on_atomic);

    for(int i = 0; i < 10; ++i)
        std::cout << data2[i];
    std::cout << '\n';
}

void test3()
{
    std::thread t1(write_index);
    std::thread t2(write_index);
    std::thread t3(write_index);
    std::thread t4(write_index);
    std::thread t5(write_index);
    std::thread t6(write_index);
    std::thread t7(write_index);
    std::thread t8(write_index);
    std::thread t9(write_index);
    std::thread t10(write_index);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();

    read_all();
}

int main()
{
    test1();
    //test2();
    //test3();

    return 0;
}



