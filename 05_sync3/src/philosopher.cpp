#include "philosopher.h"

#include <mutex>
#include <thread>
#include <chrono>

#include <iostream>
#include <iomanip>
// #include <sstream>
// #include <string>

using namespace std;

void Philosopher::operator()(){
    while(true){
        cout << "Philosopher " + to_string(id) + " is thinking...\n";

        this_thread::sleep_for(chrono::milliseconds(1000));

        cout << "Philosopher " + to_string(id) + " attempts to get left fork\n";

        fork1.lock();

        cout << "Philosopher " + to_string(id) + " got left fork. Now he wants the right one...\n";

        fork2.lock();

        cout << "Philosopher " + to_string(id) + " got right fork. Now he is eating...\n";

        this_thread::sleep_for(chrono::milliseconds(2000));

        cout << "Philosopher " + to_string(id) + " finished eating\n";

        fork1.unlock();
        fork2.unlock();

        cout << "Philosopher " + to_string(id) + " released left fork\n";
        cout << "Philosopher " + to_string(id) + " released right fork\n";

    }
}