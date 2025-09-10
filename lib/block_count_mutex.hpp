#ifndef BLOCK_COUNT_MUTEX_HPP
#define BLOCK_COUNT_MUTEX_HPP

#include <atomic>
#include <mutex>
#include <thread>

class Block_Count_Mutex {
public:
    Block_Count_Mutex();

    void lock();
    void unlock();
    bool try_lock();
    int get_blocked_count() const;

private:
    std::mutex mtx;
    std::atomic<int> blocked_count;
};

#endif // BLOCK_COUNT_MUTEX_HPP