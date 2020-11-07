#pragma once

#include "work_packet.h"

#include <queue>
#include <mutex>

class WorkQueue {
    private:
        std::queue<WorkPacket> queue;
        std::mutex m;
    public:
        void push(WorkPacket);
        WorkPacket pop();
};