#pragma once

#include "philosopher.h"
#include "semaphore.h"

#include <mutex>

class Philosopher {
    private:
        int id;
        std::timed_mutex& fork1;
        std::timed_mutex& fork2;
        Semaphore *seamphore;
        bool livelock;
    public:
        Philosopher( int id
                   , std::timed_mutex& fork1
                   , std::timed_mutex& fork2
                   , Semaphore *seamphore
                   , bool livelock): 
                   id(id),
                   fork1(fork1),
                   fork2(fork2),
                   seamphore(seamphore),
                   livelock(livelock)
                   {};

        void operator()();
};