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
    long long get_blocked_time_ns() const;

private:
    std::mutex mtx;
    std::atomic<int> blocked_count;
    std::atomic<long long> blocked_time_ns;
};

class Spin_Lock {
public:
    void lock();
    void unlock();

private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

#endif // BLOCK_COUNT_MUTEX_HPP