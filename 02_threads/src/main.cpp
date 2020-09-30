#include "../include/car.h"

#include <iostream>
#include <thread>
#include <string>

using namespace std;


void error(string msg=""){
    if(msg != ""){
        cout << msg << endl;
    }    
    cout << "Run with --help for more information." << endl;
}

void help(){
    cout << "Usage: contest [-h | --help | LAPS]" << endl;
}


int main(int argc, char* argv[]) {

    int value;

    if(argc == 1){
        value = 10;
    } else {
        if(argc > 2){
            error("too many arguments");
            quick_exit(1);
        }

        string stringValue = argv[1];

        if(stringValue == "-h" || stringValue == "--help"){
            help();
            quick_exit(EXIT_SUCCESS);
        }

        try {
            size_t pos;
            value = stoi(stringValue, &pos);
            if (pos != stringValue.size()){
                throw 1;
            }
        } catch (...) {
            error("Could not convert: " + stringValue);
            quick_exit(1);
        }

        if(value < 1 || value > 15){
            error("Out of range (1 <= LAP'S < 16): 0");
            quick_exit(EXIT_SUCCESS);
        }
    }

    Car car1("Opel Corsa");
    Car car2("Opel Manta");

    thread t1{ref(car1), value};
    thread t2{ref(car2), value};

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
