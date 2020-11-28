#include "philosopher.h"

#include <mutex>
#include <thread>
#include <chrono>

#include <iostream>
#include <iomanip>
#include <string>

#include <vector>

using namespace std;

void Philosopher::operator()(){
    while(true){
        cout << "Philosopher " + to_string(id) + " is thinking...\n" << flush;

        this_thread::sleep_for(chrono::milliseconds(1000));

        cout << "Philosopher " + to_string(id) + " attempts to get left fork\n" << flush;

        fork1.lock();

        cout << "Philosopher " + to_string(id) + " got left fork. Now he wants the right one...\n" << flush;

        fork2.lock();

        cout << "Philosopher " + to_string(id) + " got right fork. Now he is eating...\n" << flush;

        this_thread::sleep_for(chrono::milliseconds(2000));

        cout << "Philosopher " + to_string(id) + " finished eating\n" << flush;

        fork1.unlock();
        fork2.unlock();

        cout << "Philosopher " + to_string(id) + " released left fork\n" << flush;
        cout << "Philosopher " + to_string(id) + " released right fork\n" << flush;

    }
}