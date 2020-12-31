#include "clock.h"
#include "pipe.h"

#include <iostream>
#include <thread>
#include <string>

using namespace std;

class Channel {
    private:
        Pipe<long> pipe1;
        Pipe<long> pipe2;
    public:
        Pipe<long> &get_pipe1() {
            return pipe1;
        }
        Pipe<long> &get_pipe2() {
            return pipe2;
        }
};

class TimeSlave {
    private:
        string name;
        Clock clock;
        Channel *channel;
    public:
        TimeSlave(string name, int hours, int minutes, int seconds) {
            this->name = name;
            clock = Clock(name, hours, minutes, seconds);
        }
        void onStart() {
            thread clockThread{ref(clock)};
            clockThread.join();
        }
        Channel* get_channel() {
            return channel;
        }
};

class TimeMaster {
    private:
        string name;
        Clock clock;
        Channel *channel1;
        Channel *channel2;
    public:
        TimeMaster(string name, int hours, int minutes, int seconds) {
            this->name = name;
            clock = Clock(name, hours, minutes, seconds);
        }
        void onStart() {
            thread clockThread{ref(clock)};
            clockThread.join();
        }
        void set_channel1(Channel* channel) {
            channel1 = channel;
        }
        void set_channel2(Channel* channel) {
            channel2 = channel;
        }
};

int main() { //int argc, char* argv[]
    TimeSlave slave1{"slave1", 0, 0, 2};
    TimeSlave slave2{"slave2", 0, 2, 20};
    TimeMaster master{"slave2", 0, 2, 0};

    master.set_channel1(slave1.get_channel());
    master.set_channel2(slave1.get_channel());

    thread t1{&TimeSlave::onStart, ref(slave1)};
    thread t2{&TimeSlave::onStart, ref(slave2)};
    thread t3{&TimeMaster::onStart, ref(master)};

    t1.join();
    t2.join();
    t3.join();
}
