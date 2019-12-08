
#include <atomic>

class mutex_on_atomic{

    std::atomic<bool> sync = true;

public:

    void lock(){
        bool expected = true;
        while(!sync.compare_exchange_strong(expected, false, std::memory_order_acq_rel))
            expected = true;
    }

    void unlock(){
        sync.store(true, std::memory_order_release);
    }
};