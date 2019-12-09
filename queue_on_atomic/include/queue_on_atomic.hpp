
#include <vector>
#include <atomic>
#include <thread>
#include <iostream>
#include <chrono>

class queue_on_atomic{

    std::vector<int> queue_data;
    std::atomic<int> count;
    std::atomic<bool> go = false;

        void wait_for_more_items()
        {
            while(!go.load(std::memory_order_acquire))
                std::this_thread::yield();
        }

    public:

        void populate()
        {
            const int number_of_items = 1000;
            queue_data.clear();
            for(int i = 0; i < number_of_items; ++i)
            {
                queue_data.push_back(i);
            }
            count.store(number_of_items, std::memory_order_release);

            //go.store(true, std::memory_order_release);

            //std::cout << "populated: " << queue_data.size() << std::endl;
        }

        void consume()
        {
            //using namespace std::chrono_literals;

            std::vector<std::pair<int,int>> q;

            //wait_for_more_items();

            while(true)
            {
                int item_index = 0;
                if ((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0)
                {
                    //wait_for_more_items();
                    break;
                }
                auto& value = queue_data[item_index - 1];
                q.push_back(std::make_pair(item_index - 1, value));

                std::this_thread::yield();
            }

            //for(auto& i: q){
            //   std::cout << std::this_thread::get_id() << ": " << "queue_data[" << i.first << "]" << "; value = " << i.second << std::endl;
            //}

            std::cout << std::this_thread::get_id() << " finished size: " << q.size() << std::endl;
        }
};