#include "philosopher.h"
#include "semaphore.h"

#include <mutex>
#include <thread>
#include <chrono>

#include <iostream>
#include <iomanip>
#include <string>

#include <vector>

using namespace std;

recursive_mutex out_mtx;

void println() {
    lock_guard<recursive_mutex> lg{out_mtx};
    cout << endl;
}

template<typename T, typename... Rest>
void println(const T& word, const Rest&... rest) {
    lock_guard<recursive_mutex> lg{out_mtx};
    cout << word;
    println(rest...);
}


void Philosopher::operator()() {
    while (true) {
        println("Philosopher ", id, " is thinking...");

        this_thread::sleep_for(chrono::seconds(1));

        bool got_fork2{false};

        do {
            if (seamphore) {
                seamphore->acquire();
            }

            println("Philosopher ", id, " attempts to get left fork");

            fork1.lock();

            println("Philosopher ", id, " got left fork. Now he wants the right one...");

            this_thread::sleep_for(chrono::seconds(5));

            if (livelock) {
                fork2.try_lock_for(chrono::seconds(3));
                if (!got_fork2) {
                    this_thread::sleep_for(chrono::milliseconds(100));
                    fork1.unlock();
                    println("Philosopher ", id, " released left fork due to timeout getting the right one!");
                    this_thread::sleep_for(chrono::seconds(3));
                }
            } else {
                fork2.lock();
                println("Philosopher ", id, " got right fork. Now he is eating...");
            }
        } while (livelock && !got_fork2);

        this_thread::sleep_for(chrono::seconds(2));

        println("Philosopher ", id, " finished eating");

        fork1.unlock();

        println("Philosopher ", id, " released left fork");

        fork2.unlock();

        println("Philosopher ", id, " released right fork");

        if (seamphore) {
            seamphore->release();
        }
    }
}