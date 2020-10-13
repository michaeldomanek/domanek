#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
    private:
        int balance;
    public:
        Account(int startAmount);
        int get_balance();
        void deposit(int amount);
        bool withdraw(int amount);
};

#endif //ACCOUNT_H