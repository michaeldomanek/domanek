#include "../include/car.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <random>
#include <iomanip>
#include <sstream>

using namespace std;

Car::Car(string carName){
    this->carName = carName;
}

void Car::operator()() {
    ostringstream buf;
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};
    double time = dis(gen);
	chrono::milliseconds sleeptime((int)time * 1000);

    for (int i=0;; i++) {
        this_thread::sleep_for(sleeptime);

        buf << i << " " << carName << " " << setprecision(3) << time << "s" << endl;
        cout << buf.str() << flush;
        buf.str(""); 
    }
}