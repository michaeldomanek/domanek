#pragma once

#include "philosopher.h"
#include "semaphore.h"

#include <mutex>

class Philosopher {
    private:
        int id;
        std::mutex& fork1;
        std::mutex& fork2;
        Semaphore *seamphore;
    public:
        Philosopher( int id, std::mutex& fork1
                   , std::mutex& fork2, Semaphore *seamphore): 
                     id(id),
                     fork1(fork1),
                     fork2(fork2),
                     seamphore(seamphore)
                     {};

        void operator()();
};