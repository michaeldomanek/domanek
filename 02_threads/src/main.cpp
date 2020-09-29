#include "../include/car.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;


void runCar(){
    for (int i=0;; i++) {
        this_thread::sleep_for(2s);
        cout << to_string(i) + " Opel Corsa\n";
    }
}

int main() {
    thread t{runCar};
    
    Car opelManta("Opel Manta");
    thread t2{opelManta};

    t.join();
    t2.join();


}
