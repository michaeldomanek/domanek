// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wmisleading-indentation"
// #pragma GCC diagnostic ignored "-Wsign-compare"
// #include "InfInt.h"
// #pragma GCC diagnostic pop

#include "CLI11.hpp"

#include <vector>
#include <string>
#include <cstddef>

using namespace std;

string callable(const std::string &str){
    if (str.find_first_not_of("0123456789") != string::npos)
        return "number: " + str + " contains not numeric character";
    return string();
}

int main(int argc, char* argv[]) {
    CLI::App app("Factor numbers");

    vector<string> stringNumbers;
    app.add_option("number", stringNumbers, "numbers to factor")->required()->check(callable);

    bool async{false};
    app.add_flag("-a,--async", async, "async");

    CLI11_PARSE(app, argc, argv);

    for (const auto& stringNumber: stringNumbers)
        cout << stringNumber << endl;
}
