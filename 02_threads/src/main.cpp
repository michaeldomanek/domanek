#include "../include/car.h"

#include <iostream>
#include <thread>

using namespace std;

int main() {
    Car car1("Opel Corsa");
    Car car2("Opel Manta");

    thread t1{ref(car1)};
    thread t2{ref(car2)};

    t1.join();
    t2.join();

    double car1Time = car1.get_total_time();
    double car2Time = car2.get_total_time();

    if(car1Time < car2Time){
        cout << "Sieger ist: " << car1.getName() << " mit " << car1Time << "s" << endl;
        cout << "Verlierer ist: " << car2.getName() << " mit " << car2Time << "s" << endl;
    } else {
        cout << "Sieger ist: " << car2.getName() << " mit " << car2Time << "s" << endl;
        cout << "Verlierer ist: " << car1.getName() << " mit " << car1Time << "s" << endl;
    }
}
