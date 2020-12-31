#include "clock.h"

#include <iostream>
#include <thread>
#include <string>

using namespace std;

class TimeSlave {
    private:
        string name;
        Clock clock;
    public:
        TimeSlave(string name, int hours, int minutes, int seconds) {
            this->name = name;
            clock = Clock(name, hours, minutes, seconds);
        }
        void onStart() {
            thread clockThread{ref(clock)};
            clockThread.join();
        }
};

int main() { //int argc, char* argv[]
    TimeSlave slave1{"slave1", 0, 0, 2};
    TimeSlave slave2{"slave2", 0, 2, 20};
    thread t1{&TimeSlave::onStart, ref(slave1)};
    thread t2{&TimeSlave::onStart, ref(slave2)};
    t1.join();
    t2.join();
}
