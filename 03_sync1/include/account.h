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

#endif //ACCOUNT_H