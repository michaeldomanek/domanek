#ifndef PIPE_H
#define PIPE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Pipe {
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable not_empty;
    bool closed{false};
  public:
    Pipe& operator<<(T value) {
        auto future{async([this, value](){
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
        std::unique_lock lck(mtx);
        not_empty.wait(lck, [&] { return queue.size() > 0; });
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
};
#endif
