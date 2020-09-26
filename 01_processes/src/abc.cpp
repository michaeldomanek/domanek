#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <csignal>
#include <cstdlib>
#include <cerrno>
#include <string>

using namespace std;

int main() {
    chrono::milliseconds sleeptime(3000);

    auto pid{fork()};
    auto pid2{fork()};

    if (pid == 0 && pid2 > 0) {
        execl("./charout", "charout", "A", nullptr);
        if (errno){
            cout << endl;
            kill(pid, SIGKILL);
            exit(1);
        }
    } else if (pid > 0 && pid2 == 0) {
        execl("./charout", "charout", "B", nullptr);
        if (errno){
            cout << endl;
            kill(pid2, SIGKILL);
            exit(1);
        }
    } else if (pid > 0 && pid2 > 0) {
        this_thread::sleep_for(sleeptime);

        cout << endl;
        kill(pid, SIGKILL);
        kill(pid2, SIGKILL);
        quick_exit(EXIT_SUCCESS);
    }
    
}