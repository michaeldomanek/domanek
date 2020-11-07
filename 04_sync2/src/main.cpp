#include "work_packet.h"

#include <iostream>

using namespace std;

int main() {
    WorkPacket wp{2};
    cout << wp.get_id() << endl;
}
