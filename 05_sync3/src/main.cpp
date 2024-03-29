#include "philosopher.h"
#include "semaphore.h"
#include "CLI11.hpp"

#include <mutex>
#include <thread>

using namespace std;


int main(int argc, char* argv[]) {
    CLI::App app("Dining philosophers simulation");

    timed_mutex f1;
    timed_mutex f2;
    timed_mutex f3;
    timed_mutex f4;
    timed_mutex f5;

    Semaphore *semaphore = nullptr;

    bool nodeadlock{false};
    app.add_flag("-n,--nodeadlock", nodeadlock, "Prevent a deadlock at all");

    bool livelock{false};
    app.add_flag("-l,--livelock", livelock, "Simulate a livelock");

    CLI11_PARSE(app, argc, argv);

    if(nodeadlock){
        semaphore = new Semaphore(4);
    }

    Philosopher p1{1, f1, f2, semaphore, livelock};
    Philosopher p2{2, f2, f3, semaphore, livelock};
    Philosopher p3{3, f3, f4, semaphore, livelock};
    Philosopher p4{4, f4, f5, semaphore, livelock};
    Philosopher p5{5, f5, f1, semaphore, livelock};

    thread t1{p1};
    thread t2{p2};
    thread t3{p3};
    thread t4{p4};
    thread t5{p5};

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}
