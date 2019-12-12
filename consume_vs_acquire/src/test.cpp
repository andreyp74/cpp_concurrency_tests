#include <atomic>
#include <chrono>
#include <thread>
#include <assert.h>

#include "person.hpp"

std::atomic<Person*> p;
std::atomic<int> a;

void create_person()
{
    Person* person = new Person;
    person->age = 42;
    person->name = "John";
    a.store(99, std::memory_order_relaxed);

    p.store(person, std::memory_order_release);
}

void use_person_consume()
{
    Person* person;
    while(!(person = p.load(std::memory_order_consume)))
        std::this_thread::sleep_for(std::chrono::microseconds(1));

    assert(person->age == 42);
    assert(person->name == "John");
    assert(a.load(std::memory_order_relaxed) == 99);
}

void use_person_aquire()
{
    Person* person;
    while(!(person = p.load(std::memory_order_acquire)))
        std::this_thread::sleep_for(std::chrono::microseconds(1));

    assert(person->age == 42);
    assert(person->name == "John");
    assert(a.load(std::memory_order_relaxed) == 99);
}

int main()
{
    std::thread t1(create_person);
    //std::thread t2(use_person_consume);
    std::thread t2(use_person_aquire);

    t1.join();
    t2.join();

    return 0;
}