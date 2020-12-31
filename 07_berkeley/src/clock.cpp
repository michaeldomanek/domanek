#include "clock.h"
#include "timeutils.h"

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <mutex>

using namespace std;

Clock::Clock(string name) {
    this->name = name;
    this->curr_time = chrono::system_clock::now();
}

Clock::Clock(string name, int hours, int minutes, int seconds){
    this->name = name;
    this->curr_time = chrono::system_clock::now();
    curr_time = ::set_time(this->curr_time, hours, minutes, seconds);
}

void Clock::set_time(int hours, int minutes, int seconds) {
    curr_time = ::set_time(curr_time, hours, minutes, seconds);
}

tuple<int, int, int> Clock::get_time() {
    return ::get_time(curr_time);
}

void Clock::operator()(){
    while (true) {
        this_thread::sleep_for(chrono::seconds(1));
        curr_time += 1s;
        {
            scoped_lock lock(mtx);
            cout << curr_time << endl;     
        }
    }
}

std::mutex Clock::mtx;