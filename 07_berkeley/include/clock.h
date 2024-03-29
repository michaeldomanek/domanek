#pragma once

#include <string>
#include <chrono>
#include <tuple>
#include <mutex>

class Clock {
    private:
        std::string name;
        std::chrono::time_point<std::chrono::system_clock> curr_time;
        static std::mutex mtx;
        bool monoton_time;
        int clock_slowdown = 0;
        int clock_speed;
    public:
        Clock(){};
        Clock(std::string name);
        Clock(std::string name, int hours, int minutes, int seconds);
        void set_time(int hours, int minutes, int seconds);
        std::tuple<int, int, int> get_time();
        long to_time();
        void from_time(long);
        void set_clock_speed(int);
        void set_time_monoton(bool);
        void operator()();
};