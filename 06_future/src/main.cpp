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

using namespace std;

string checkString(const std::string &str){
    if (str.find_first_not_of("0123456789") != string::npos)
        return "number: " + str + " contains not numeric character";
    return string();
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

    vector<shared_future<vector<InfInt>>> futures;
    for (const auto& number: numbers) {
        shared_future<vector<InfInt>> primeFactors{async(get_factors, number)};
        futures.push_back(primeFactors);
    }

    for(vector<InfInt>::size_type i = 0; i != numbers.size(); i++) {
        cout << numbers[i] << ": ";
        
        for (const auto& primeNumber: futures[i].get()) {
            cout << primeNumber << ' ';
        }

        cout << endl;
    }
}
