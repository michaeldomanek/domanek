#include "philosopher.h"

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
    while(true){
        println("Philosopher ", to_string(id), " is thinking...");

        this_thread::sleep_for(chrono::milliseconds(1000));

        println("Philosopher ", to_string(id), " attempts to get left fork");

        fork1.lock();

        println("Philosopher ", to_string(id), " got left fork. Now he wants the right one...");

        fork2.lock();

        println("Philosopher ", to_string(id), " got right fork. Now he is eating...");

        this_thread::sleep_for(chrono::milliseconds(2000));

        println("Philosopher ", to_string(id), " finished eating");

        fork1.unlock();
        fork2.unlock();

        println("Philosopher ", to_string(id), " released left fork");
        println("Philosopher ", to_string(id), " released right fork");

    }
}