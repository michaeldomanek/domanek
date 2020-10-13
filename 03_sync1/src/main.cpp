#include "account.h"

#include <iostream>
#include <thread>

using namespace std;

int main() {
    Account acc = Account(1);

    auto deposit = [](Account& acc) {
        cout << "Withdraw erfolgreich: " << acc.withdraw(1) << endl;
    };
    thread t1{deposit, ref(acc)};
    thread t2{deposit, ref(acc)};
    t1.join();    
    t2.join();

    // Punkt 1
    cout << "Balance: " << acc.get_balance() << endl;
    // acc.deposit(6);
    // cout << "Balance: " << acc.get_balance() << endl;
    // cout << "Withdraw erfolgreich: " << acc.withdraw(3) << endl;
    // cout << "Balance: " << acc.get_balance() << endl;
    // cout << "Withdraw erfolgreich: " << acc.withdraw(10) << endl;
    // cout << "Balance: " << acc.get_balance() << endl;
}
