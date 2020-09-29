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
    totalTime = 0;
}

void Car::operator()() {
    ostringstream buf;
    std::random_device rd;

    for (int i=0; i < 10; i++) {
        std::mt19937 gen{rd()};
        std::uniform_real_distribution<> dis{1, 10};
        
        double time = dis(gen);
        totalTime += time;

        chrono::milliseconds sleeptime((int)time);
        this_thread::sleep_for(sleeptime);

        buf << i << " " << carName << " " << setprecision(3) << time << "s" << endl;
        cout << buf.str() << flush;
        buf.str(""); 
    }
}

double Car::get_total_time(){
    return totalTime;
}

string Car::getName(){
    return carName;
}