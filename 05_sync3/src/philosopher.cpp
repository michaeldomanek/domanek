#include "philosopher.h"

#include <mutex>
#include <thread>
#include <chrono>

#include <iostream>
#include <iomanip>
#include <string>

#include <vector>

using namespace std;

void println(const initializer_list<string>& messages){
    string output = "";
    for (auto message: messages){
        output += message;
    }
    output += '\n';
    cout << output << flush;
}

void Philosopher::operator()(){
    while(true){
        println({"Philosopher ", to_string(id), " is thinking..."});

        this_thread::sleep_for(chrono::milliseconds(1000));

        println({"Philosopher ", to_string(id), " attempts to get left fork"});

        fork1.lock();

        println({"Philosopher ", to_string(id), " got left fork. Now he wants the right one..."});

        fork2.lock();

        println({"Philosopher ", to_string(id), " got right fork. Now he is eating..."});

        this_thread::sleep_for(chrono::milliseconds(2000));

        println({"Philosopher ", to_string(id), " finished eating"});

        fork1.unlock();
        fork2.unlock();

        println({"Philosopher ", to_string(id), " released left fork"});
        println({"Philosopher ", to_string(id), " released right fork"});

    }
}