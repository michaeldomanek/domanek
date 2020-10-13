#include "account.h"

#include <iostream>
#include <thread>
// #include <mutex>

using namespace std;

Account::Account(int amount){
    balance = amount;
}

int Account::get_balance(){
    return balance;
}

void Account::deposit(int amount){
    int tmp{balance};
    this_thread::sleep_for(10ms);
    balance = tmp + amount;
}

bool Account::withdraw(int amount){
    lock_guard<mutex> guard{m};
    if(balance >= amount){
        balance -= amount;
        this_thread::yield();
        return true;
    }
    return false;
}