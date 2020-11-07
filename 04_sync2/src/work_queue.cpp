#include "work_packet.h"
#include "work_queue.h"

#include <thread>
#include <mutex>

using namespace std;

void WorkQueue::push(WorkPacket wp){
    lock_guard<mutex> lck{m};
    queue.push(wp);
}

WorkPacket WorkQueue::pop(){
    unique_lock<mutex> lck{m};
    WorkPacket wp = queue.front();
    queue.pop();
    return wp;
}