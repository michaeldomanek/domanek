#include "../include/car.h"

#include <iostream>
#include <thread>
#include <string>

using namespace std;

Car::Car(string carName){
    this->carName = carName;
}

void Car::operator()() {
    for (int i=0;; i++) {
        this_thread::sleep_for(2s);
        cout << to_string(i) + " " + carName + "\n";
    }
}