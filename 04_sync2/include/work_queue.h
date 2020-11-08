#pragma once

#include "work_packet.h"

#include <queue>
#include <mutex>
#include <condition_variable>


class WorkQueue {
    private:
        std::queue<WorkPacket> queue;
        std::mutex m;
        std::condition_variable not_empty;
        std::condition_variable not_full;
        std::size_t size;
    public:
        WorkQueue(unsigned int size): size(size){};
        void push(WorkPacket);
        WorkPacket pop();
};