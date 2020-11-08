#include "work_packet.h"
#include "work_queue.h"

#include <thread>
#include <mutex>

using namespace std;

void WorkQueue::push(WorkPacket wp) {
    unique_lock<mutex> lock{m};
    not_full.wait(lock, [this]{ return queue.size() < size; });  

    queue.push(wp);
    not_empty.notify_one();
}

WorkPacket WorkQueue::pop() {
    unique_lock<mutex> lock{m};
    not_empty.wait(lock, [this]{ return queue.size();});
    
    WorkPacket wp{queue.front()};
    queue.pop();
    not_full.notify_one();

    return wp;
}