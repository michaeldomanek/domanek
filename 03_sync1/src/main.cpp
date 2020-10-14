#include "account.h"
#include "CLI11.hpp"

#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char* argv[]) {
    CLI::App app("Account app");

    int balance{0};
    app.add_option("balance", balance, "Initial balance")->required();
    
    int deposits{5};
    app.add_option("-d,--deposits", deposits, "Count of deposits", true);
    
    CLI11_PARSE(app, argc, argv);

    Account acc{balance};

    thread t1{Depositer{ref(acc), deposits}};
    thread t2{Depositer{ref(acc), deposits}};

    t1.join();
    t2.join();

    cout << "Balance: " << acc.get_balance() << endl;
}
