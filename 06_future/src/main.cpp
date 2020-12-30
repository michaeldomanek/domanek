#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "InfInt.h"
#pragma GCC diagnostic pop

#include "calc_factors.h"

#include "CLI11.hpp"

#include <vector>
#include <string>
#include <future>
#include <thread>
#include <chrono>

using namespace std;

string checkString(const string &str){
    if (str.find_first_not_of("0123456789") != string::npos)
        return "number: " + str + " contains not numeric character";
    return string();
}


void printPrimes(vector<InfInt> numbers, vector<shared_future<vector<InfInt>>> futures) {
    for(vector<InfInt>::size_type i = 0; i != numbers.size(); i++) {
        cout << numbers[i] << ": ";
        
        for (const auto& primeNumber: futures[i].get()) {
            cout << primeNumber << ' ';
        }

        cout << endl;
    }
}


void checkFactors(vector<InfInt> numbers, vector<shared_future<vector<InfInt>>> futures) {
    for(vector<InfInt>::size_type i = 0; i != numbers.size(); i++) {
        InfInt sum = 1;
        for (const auto& primeNumber: futures[i].get()) {
            sum *= primeNumber;
        }

        if(sum != numbers[i]){
            cerr << "\nerror with number: " + numbers[i].toString() + "\n" << flush;
        }
        
    }
}


int main(int argc, char* argv[]) {
    CLI::App app("Factor numbers");

    vector<InfInt> numbers;

    vector<string> stringNumbers;
    app.add_option("number", stringNumbers, "numbers to factor")->required()->check(checkString);

    bool isAsync{false};
    app.add_flag("-a,--async", isAsync, "async");

    CLI11_PARSE(app, argc, argv);

    for (const auto& stringNumber: stringNumbers){
        numbers.push_back(stringNumber);
    }

    auto start = chrono::system_clock::now();

    vector<shared_future<vector<InfInt>>> futures;
    for (const auto& number: numbers) {
        if(isAsync){
            shared_future<vector<InfInt>> primeFactors{async(launch::async, get_factors, number)};
            futures.push_back(primeFactors);
        } else {
            shared_future<vector<InfInt>> primeFactors{async(launch::deferred, get_factors, number)};
            futures.push_back(primeFactors);
        }
    }

    thread t{checkFactors, numbers, futures};

    printPrimes(numbers, futures);

    auto duration = chrono::duration_cast<chrono::milliseconds>
        (std::chrono::system_clock::now() - start);
    cout << "Time elapsed used for factoring: " << duration.count() << "ms" << endl;

    t.join();
}
