#include "philosopher.h"

#include <mutex>
#include <thread>

using namespace std;


int main() {
    mutex f1;
    mutex f2;
    mutex f3;
    mutex f4;
    mutex f5;

    Philosopher p1{1, f1, f2};
    Philosopher p2{2, f2, f3};
    Philosopher p3{3, f3, f4};
    Philosopher p4{4, f4, f5};
    Philosopher p5{5, f5, f1};

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
