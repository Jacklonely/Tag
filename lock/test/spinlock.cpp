/*
#include "timer.h"

#include <atomic>
#include <mutex>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


using namespace std;
#define PTHREADNUM 10
#define LOOPNUM 2000000

class spin_mutex
{
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
//    std::atomic_flag flag = ATOMIC_VAR_INIT(false);
public:
    spin_mutex() = default;
    spin_mutex(const spin_mutex&) = delete;
    spin_mutex& operator= (const spin_mutex&) = delete;
    void lock()
    {
        while (flag.test_and_set(std::memory_order_acquire));
    }

    void unlock()
    {
        flag.clear(std::memory_order_release);
    }
};

int count = 0;
spin_mutex sm;

void* thread_proc(void* arg)
{
    for(int i = 0; i < LOOPNUM; i++)
    {
        // lock_guard 鑷В閿? lock mutex
        std::lock_guard<spin_mutex> lock(sm);
        //do something might throw exception
        //...
//        sm.lock();
        ++count;
//        sm.unlock();
        //do not unlock mutex, it will be unlocked by lock_guard destructor
    }
}

int main()
{
    Timer timer;
    timer.start();

#if 1
    pthread_t thread_ids[PTHREADNUM];

    for (int i = 0; i < PTHREADNUM; i++)
    {
        pthread_create(&thread_ids[i], nullptr, thread_proc, nullptr);
    }

    for (int i = 0; i < PTHREADNUM; i++)
    {
        pthread_join(thread_ids[i], nullptr);
    }
#endif

    timer.stop();
    timer.costTime();
    printf("result: count = %d\n", count);

    return 0;
}
*/
