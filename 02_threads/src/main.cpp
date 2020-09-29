#include "../include/car.h"

#include <iostream>
#include <thread>

using namespace std;

int main() {
    Car opelCorsa("Opel Corsa");
    thread t1{opelCorsa};
    
    Car opelManta("Opel Manta");
    thread t2{opelManta};

    t1.join();
    t2.join();
}
