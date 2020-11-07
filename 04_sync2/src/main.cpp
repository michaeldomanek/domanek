#include "work_packet.h"
#include "work_queue.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    WorkQueue wq{};
    chrono::milliseconds sleeptime(500);

    for(int i{0};; i++){
        WorkPacket wp{i};    
        wq.push(wp);
        cout << "B: Submitted work packet " << i << endl;
        this_thread::sleep_for(sleeptime);
    }
}
