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
    balance += amount;
}

bool Account::withdraw(int amount){
    int newBalance;
    if(balance >= amount){
        newBalance = balance - amount;
        this_thread::yield();
        balance = amount;
        return true;
    }
    return false;
    
}
