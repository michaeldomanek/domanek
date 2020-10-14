#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <mutex>

class Account {
    private:
        int balance;
        std::mutex m;
    public:
        Account(int startAmount);
        int get_balance();
        void deposit(int amount);
        bool withdraw(int amount);
};

class Depositer {
    private:
        Account& account;
        int count;
    public:
        Depositer(Account& acc, int depositCount):
            account(acc), 
            count(depositCount)
            {};
        
        void operator()(){
            for(int i = 0; i < count; i++){
                account.deposit(1);
            }
        }
};

#endif //ACCOUNT_H