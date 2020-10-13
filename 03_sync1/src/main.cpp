#include "car.h"

#include <iostream>

using namespace std;

int main() {
    Account acc = Account(1);
    cout << "Balance: " << acc.get_balance() << endl;
    acc.deposit(6);
    cout << "Balance: " << acc.get_balance() << endl;
    cout << "Withdraw erfolgreich: " << acc.withdraw(3) << endl;
    cout << "Balance: " << acc.get_balance() << endl;
    cout << "Withdraw erfolgreich: " << acc.withdraw(10) << endl;
    cout << "Balance: " << acc.get_balance() << endl;
}
