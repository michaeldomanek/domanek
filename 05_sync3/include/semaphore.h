#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore {
  private:
    unsigned int size;
    std::mutex mtx;
    std::condition_variable notEmpty;

  public:
    Semaphore(): size(1){};
    Semaphore(unsigned int size): size(size){};

    int avalible_permits();
    void acquire();
    void release();
};