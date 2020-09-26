#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <csignal>
#include <cstdlib>

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
            if (++counter == 6){
                cout << endl;
                kill(pid, SIGKILL);
                // cout << pid << endl;
                // sleep(10);
                quick_exit(EXIT_SUCCESS);
            }
        }
    }
}