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
        void set_latency(int latency) {
            pipe1.set_latency(latency);
            pipe2.set_latency(latency);
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
            channel = new Channel();
        }
        void on_start() {
            thread clockThread{ref(clock)};

            Pipe<long> &masterPipe = channel->get_pipe1();
            Pipe<long> &slavePipe = channel->get_pipe2();

            long time;
            while (masterPipe >> time) {
                if (time == 0) {
                    slavePipe << clock.to_time();
                } else {
                    clock.from_time(time);
                }
            }

            clockThread.join();
        }
        Channel* get_channel() {
            return channel;
        }
        void set_time_monoton(bool value) {
            clock.set_time_monoton(value);
        }

        void set_clock_speed(int speed) {
            clock.set_clock_speed(speed);
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
        void on_start() {
            thread clockThread{ref(clock)};

            while (true) {
                this_thread::sleep_for(chrono::milliseconds(500));
                channel1->get_pipe1() << 0;
                channel2->get_pipe1() << 0;

                long timeSlave1;
                channel1->get_pipe2() >> timeSlave1;
                long timeSlave2;
                channel2->get_pipe2() >> timeSlave2;
                long ownTime = clock.to_time();

                long finalTime = timeSlave1 + timeSlave2 + ownTime;
                finalTime = finalTime / 3;

                channel1->get_pipe1() << finalTime;
                channel2->get_pipe1() << finalTime;
                clock.from_time(finalTime);
            }

            clockThread.join();
        }
        void set_channel1(Channel* channel) {
            channel1 = channel;
        }
        void set_channel2(Channel* channel) {
            channel2 = channel;
        }
        void set_time_monoton(bool value) {
            clock.set_time_monoton(value);
        }

        void set_clock_speed(int speed) {
            clock.set_clock_speed(speed);
        }
};

int main() { //int argc, char* argv[]
    bool monoton = false;
    int delay1{};
    int delay2{};
    int rateM{1000};
    int rate1{1000};
    int rate2{1000};

    TimeSlave slave1{"slave1", 0, 0, 12};
    TimeSlave slave2{"slave2", 0, 0, 22};
    TimeMaster master{"master", 0, 0, 42};

    slave1.set_time_monoton(monoton);
    slave2.set_time_monoton(monoton);
    master.set_time_monoton(monoton);
    
    slave1.get_channel()->set_latency(delay1);
    slave2.get_channel()->set_latency(delay2);

    slave1.set_clock_speed(rate1);
    slave2.set_clock_speed(rate2);
    master.set_clock_speed(rateM);
    
    master.set_channel1(slave1.get_channel());
    master.set_channel2(slave1.get_channel());

    thread t1{&TimeSlave::on_start, ref(slave1)};
    thread t2{&TimeSlave::on_start, ref(slave2)};
    thread t3{&TimeMaster::on_start, ref(master)};

    t1.join();
    t2.join();
    t3.join();
}
