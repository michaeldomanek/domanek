#include "work_packet.h"
#include "work_queue.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void worker(int id, WorkQueue& wq){
    chrono::milliseconds sleeptime(1000);

    while(true){
        string worker = "W" + to_string(id);
        cout << worker + ": Want work packet\n";
        WorkPacket wp = wq.pop();
        cout << worker +  ": Got work packet " + to_string(wp.get_id()) + "\n";
        this_thread::sleep_for(sleeptime);
        cout << worker +  ": Processed work packet " + to_string(wp.get_id()) + "\n";      
    }
}

int main() {
    WorkQueue wq{};
    chrono::milliseconds sleeptime(500);

    thread w1{worker, 1, ref(wq)};
    thread w2{worker, 2, ref(wq)};

    w1.detach();
    w2.detach();

    for (int i{0};; i++) {
        WorkPacket wp{i};    
        wq.push(wp);
        cout << "B: Submitted work packet " + to_string(i) + "\n";
        this_thread::sleep_for(sleeptime);
    }
}
