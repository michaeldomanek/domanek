#include "semaphore.h"

#include <mutex>


int Semaphore::avalible_permits() {
    return size;
}

void Semaphore::acquire() {
    std::unique_lock<std::mutex> lock(mtx);
    notEmpty.wait(lock, [this] { return size > 0; });
    size -= 1;
}

void Semaphore::release() {
    std::unique_lock<std::mutex> lock(mtx);
    size += 1;
    notEmpty.notify_one();
}