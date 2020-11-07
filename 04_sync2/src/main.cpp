#include "work_packet.h"
#include "work_queue.h"

#include <iostream>

using namespace std;

int main() {
    WorkPacket wp1{3};
    WorkPacket wp2{2};
    WorkQueue wq{};
    wq.push(wp1);
    wq.push(wp2);
    cout << wq.pop().get_id() << endl;
    cout << wq.pop().get_id() << endl;
}
