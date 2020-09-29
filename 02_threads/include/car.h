#ifndef CAR_H
#define CAR_H

#include <string>

class Car {
    private:
        std::string carName;
    public:
        Car(std::string carName);

        void operator()();
};

#endif //CAR_H