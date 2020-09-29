#include "../include/car.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <random>

using namespace std;

Car::Car(string carName){
    this->carName = carName;
}

void Car::operator()() {
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};
	chrono::milliseconds sleeptime((int)dis(gen) * 1000);
    for (int i=0;; i++) {
        this_thread::sleep_for(sleeptime);
        cout << to_string(i) + " " + carName + "\n";
    }
}