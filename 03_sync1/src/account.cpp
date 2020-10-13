#include "car.h"

#include <iostream>
#include <thread>

using namespace std;

Account::Account(int amount){
    balance = amount;
}

int Account::get_balance(){
    return balance;
}

void Account::deposit(int amount){
    balance += amount;
}

bool Account::withdraw(int amount){
    if(balance >= amount){
        balance -= amount;
        return true;
    }
    return false;
    
}
