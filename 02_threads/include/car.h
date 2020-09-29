#ifndef CAR_H
#define CAR_H

#include <string>

class Car {
    private:
        std::string carName;
        double totalTime;
    public:
        Car(std::string carName);

        void operator()(int value);

        double get_total_time();

        std::string getName();
};

#endif //CAR_H