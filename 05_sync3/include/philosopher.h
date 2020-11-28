#pragma once

#include "philosopher.h"

#include <mutex>

class Philosopher {
    private:
        int id;
        std::mutex& fork1;
        std::mutex& fork2;
    public:
        Philosopher(int id, std::mutex& fork1, std::mutex& fork2): 
          id(id),
          fork1(fork1),
          fork2(fork2)
          {};

        void operator()();
};