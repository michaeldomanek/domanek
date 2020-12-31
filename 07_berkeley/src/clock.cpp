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
    clock_speed = 1000;
}

void Clock::set_time(int hours, int minutes, int seconds) {
    auto time = ::set_time(curr_time, hours, minutes, seconds);
    if (time < curr_time) {
        clock_slowdown = 250;
    } else {
        clock_slowdown = 0;
        curr_time = ::set_time(curr_time, hours, minutes, seconds);
    }
}

tuple<int, int, int> Clock::get_time() {
    return ::get_time(curr_time);
}

void Clock::operator()(){
    while (true) {
        {
            scoped_lock lock(mtx);
            cout << curr_time << endl;     
        }
        this_thread::sleep_for(chrono::milliseconds(clock_speed + clock_slowdown));
        curr_time += 1s;
        
    }
}

long Clock::to_time() {
    return chrono::system_clock::to_time_t(curr_time);
}

void Clock::from_time(long time) {
    curr_time = chrono::system_clock::from_time_t(time);
}

void Clock::set_clock_speed(int speed) {
    clock_speed = speed;
}

void Clock::set_time_monoton(bool value) {
    monoton_time = value;
}

std::mutex Clock::mtx;