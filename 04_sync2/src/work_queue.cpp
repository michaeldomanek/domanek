#include "work_packet.h"
#include "work_queue.h"

#include <thread>
#include <mutex>

using namespace std;

void WorkQueue::push(WorkPacket wp) {
    lock_guard<mutex> lock{m};
    queue.push(wp);
    not_empty.notify_one();
}

WorkPacket WorkQueue::pop() {
    unique_lock<mutex> lock{m};
    not_empty.wait(lock, [this]{ return queue.size();});
    WorkPacket wp{queue.front()};
    queue.pop();
    return wp;
}