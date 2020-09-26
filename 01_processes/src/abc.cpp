#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    auto pid{fork()};
    auto counter = 0;
    
    chrono::milliseconds sleeptime(500);

    if (pid == 0) {
        while (true){
            cout << "A" << flush;
            this_thread::sleep_for(sleeptime);
        }
    } else {
        while (true){
            cout << "B" << flush;
            this_thread::sleep_for(sleeptime);
        }
    }
}