#include <iostream>
#include <unistd.h>
#include <chrono>

using namespace std;

int main() {
    auto pid{fork()};

    if (pid == 0) {
        while (true){
            cout << "AD" << flush;
            std::chrono::milliseconds sleeptime(1000); //sleep(1) doesn't work
        }
    } else {
        while (true){
            cout << "B" << flush;
            std::chrono::milliseconds sleeptime(1000);
        }
    }
}