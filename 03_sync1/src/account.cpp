#include "account.h"

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
    unique_lock<mutex> ul{m};
    balance += amount;
}

bool Account::withdraw(int amount){
    lock_guard<mutex> guard{m};
    if(balance >= amount){
        balance -= amount;
        return true;
    }
    return false;
}