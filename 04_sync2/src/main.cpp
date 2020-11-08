#include "work_packet.h"
#include "work_queue.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

void worker(int id, WorkQueue& wq){
    ostringstream buf;
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};

    while(true){
        double time{dis(gen)};

        buf << "W" << id << ": Want work packet" << endl;
        cout << buf.str() << flush;
        buf.str("");

        WorkPacket wp = wq.pop();

        buf << "W" << id << ": Got work packet " << wp.get_id() << endl;
        cout << buf.str() << flush;
        buf.str("");

        chrono::milliseconds sleeptime((int)(time * 1000));
        this_thread::sleep_for(sleeptime);

        buf << "W" << id << ": Processed work packet " << wp.get_id() 
            << " (" << setprecision(2) << time << "s)" << endl;
        cout << buf.str() << flush;
        buf.str("");
    }
}

int main() {
    WorkQueue wq{};
    ostringstream buf;
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{0, 1};

    thread w1{worker, 1, ref(wq)};
    thread w2{worker, 2, ref(wq)};
    thread w3{worker, 3, ref(wq)};

    w1.detach();
    w2.detach();
    w3.detach();

    for (int i{0};; i++) {
        double time{dis(gen)};
        chrono::milliseconds sleeptime((int)(time * 1000));
        
        WorkPacket wp{i};    

        buf << "B:  Waiting to submit work packet " << i << endl;
        cout << buf.str() << flush;
        buf.str("");

        wq.push(wp);
        buf << "B:  Submitted work packet" << i 
            << " (" << setprecision(2) << time << "s)" << endl;
        cout << buf.str() << flush;
        buf.str("");

        this_thread::sleep_for(sleeptime);
    }
}
