#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    auto pid{fork()};
    // chrono::milliseconds sleeptime(1000);
    if (pid == 0) {
        while (true){
            cout << "X" << flush;
            // std::chrono::milliseconds sleeptime(1000); //sleep(1) doesn't work
            // this_thread::sleep_for(sleeptime);
            fflush(stdout);
            sleep(1000);
        }
    } else {
        while (true){
            cout << "-" << flush;
            // this_thread::sleep_for(sleeptime);
            sleep(1000);
        }
    }
}