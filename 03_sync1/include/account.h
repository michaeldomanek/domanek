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
        // std::mutex m;
    public:
        Depositer(Account& acc): account(acc){};
        
        void operator()(){
            // std::unique_lock<std::mutex> ul{m};
            std::lock_guard<std::mutex> ul{m};
            for(int i = 0; i < 5; i++){
                account.deposit(1);
            }
        }
};

#endif //ACCOUNT_H