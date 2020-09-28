#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <csignal>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <sys/wait.h>

using namespace std;

void outputEnvironmentVariable(auto environmentVariableName){
    const char* environmentVariable{getenv(environmentVariableName)};
    if (environmentVariable){
        execl("./charout", "charout", environmentVariable, nullptr);
        if (errno){
            cout << strerror(errno) << endl;
            quick_exit(1);
        }
    } else {
        cout << environmentVariableName << " doesn't exists!" << endl;
    }
}

int main() {
    chrono::milliseconds sleeptime(3000);

    auto pid{fork()};
    auto pid2{fork()};

    if (pid == 0 && pid2 > 0) {
        outputEnvironmentVariable("ABA_LETTER_A");
    } else if (pid > 0 && pid2 == 0) {
        outputEnvironmentVariable("ABA_LETTER_B");
    } else if (pid > 0 && pid2 > 0) {
        int status;
        int status2;

        cout << "waiting for 3 seconds" << endl;
        this_thread::sleep_for(sleeptime);

        cout << endl << "killing both subprocesses with pids " << pid << " and " << pid2 << endl;
        kill(pid, SIGKILL);
        kill(pid2, SIGKILL);

        cout << "waiting for both subprocesses to be dead" << endl;
        waitpid(pid, &status, 0);
        waitpid(pid2, &status2, 0);
        cout << "subprocess " << pid << " exited with " << WEXITSTATUS(status) << endl;
        cout << "subprocess " << pid2 << " exited with " << WEXITSTATUS(status2) << endl;

        quick_exit(EXIT_SUCCESS);
    }    
}