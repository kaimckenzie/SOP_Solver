#include "block_count_mutex.hpp"

Block_Count_Mutex::Block_Count_Mutex() : blocked_count(0) {}

void Block_Count_Mutex::lock() {
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