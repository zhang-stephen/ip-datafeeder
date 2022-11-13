#include "log.hh"

#include <chrono>
#include <thread>

int main(int c, char** v)
{
    datafeeder::logger::init();

    auto fn = []
    {
        for (int i = 0; i < 10; i++)
        {
            LOG_INFO << "thread: " << std::this_thread::get_id();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    };

    std::thread t1(fn);
    std::thread t2(fn);

    t1.join();
    t2.join();

    return 0;
}

// EOF