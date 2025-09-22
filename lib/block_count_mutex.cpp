#include "block_count_mutex.hpp"

Block_Count_Mutex::Block_Count_Mutex()
    : blocked_count(0), blocked_time_ns(0) {}

void Block_Count_Mutex::lock() {
    auto start_time = std::chrono::high_resolution_clock::now();
#ifdef BLOCK_COUNT_SPIN_LOCK
    // spin lock
    while (!mtx.try_lock()) {
        blocked_count++;
        std::this_thread::yield();
    }
#else
    // lock check
    if (!mtx.try_lock()) {
        blocked_count++;
        mtx.lock();
    }
#endif
    auto end_time = std::chrono::high_resolution_clock::now();
    blocked_time_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
}

void Block_Count_Mutex::unlock() {
    mtx.unlock();
}

bool Block_Count_Mutex::try_lock() {
    return mtx.try_lock();
}

int Block_Count_Mutex::get_blocked_count() const {
    return blocked_count.load();
}

long long Block_Count_Mutex::get_blocked_time_ns() const {
    return blocked_time_ns.load();
}
