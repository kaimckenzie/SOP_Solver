#include <atomic>
#include <mutex>

class Block_Count_Mutex {
public:
    Block_Count_Mutex() : blocked_count(0) {}

    void lock() {
        while (!mtx.try_lock()) {
            blocked_count++;
            std::this_thread::yield();
        }
    }

    void unlock() {
        mtx.unlock();
    }

    bool try_lock() {
        return mtx.try_lock();
    }

    int get_blocked_count() const {
        return blocked_count.load();
    }

private:
    std::mutex mtx;
    std::atomic<int> blocked_count;
};
