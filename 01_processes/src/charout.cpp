#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <csignal>
#include <cstdlib>

using namespace std;

int main(int, char *argv[]) {
    chrono::milliseconds sleeptime(500);
    
    while (true){
        cout << argv[1] << flush;
        this_thread::sleep_for(sleeptime);
    }
}