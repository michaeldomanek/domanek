#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <csignal>
#include <cstdlib>
#include <cerrno>
#include <cstring>

using namespace std;

int main() {
    auto pid{fork()};
    auto counter = 0;
    
    chrono::milliseconds sleeptime(500);

    if (pid == 0) {
        execl("./charout", "charout", "A", nullptr);
        if (errno){
            cout << endl;
            kill(pid, SIGKILL);
            exit(1);
        }
    } else {
        while (true){
            cout << "B" << flush;
            this_thread::sleep_for(sleeptime);
            
            if (++counter == 6){
                cout << endl;
                kill(pid, SIGKILL);
                quick_exit(EXIT_SUCCESS);
            }
        }
    }
}