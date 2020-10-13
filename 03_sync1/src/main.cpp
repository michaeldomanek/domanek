#include "account.h"

#include <iostream>
#include <thread>

using namespace std;

int main() {
    auto deposit = [](Account& acc) {
        string success = acc.withdraw(1) ? "true" : "false";
        cout << "Withdraw erfolgreich: " + success + "\n";
        cout << "Balance: " << acc.get_balance() << endl;
    };

    Account acc = Account(1);

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
