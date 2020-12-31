#ifndef PIPE_H
#define PIPE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <future>

template <typename T>
class Pipe {
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable not_empty;
    bool closed{false};
    int latency;
  public:
    Pipe& operator<<(T value) {
        auto future{std::async([this, value](){
            std::this_thread::sleep_for(std::chrono::seconds(latency));
            std::unique_lock lck(mtx);
            queue.push(value);
            not_empty.notify_one();
        })};
        
        return *this;
    }
    
    Pipe& operator>>(T& value) {
        if (closed) {
            return *this;
        }
        std::unique_lock lock(mtx);
        not_empty.wait(lock, [&] { return queue.size() > 0; });
        value = queue.front();
        queue.pop();
        return *this;
    }

    void close() {
        closed = true;
    }
    
    explicit operator bool() {
        return !closed;
    }

    void set_latency(int latency) {
        this->latency = latency;
    }
};
#endif
