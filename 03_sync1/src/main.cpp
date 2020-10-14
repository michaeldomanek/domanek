#include "account.h"

#include <iostream>
#include <thread>

using namespace std;

int main() {
    Account acc{0};

    thread t1{Depositer{ref(acc), 6}};
    thread t2{Depositer{ref(acc), 3}};

    t1.join();
    t2.join();
}
