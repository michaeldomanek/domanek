#pragma once

class WorkPacket {
    private:
        const int id;
    public:
        WorkPacket(int id): id(id){};
        int get_id() const {
            return id;
        }
};