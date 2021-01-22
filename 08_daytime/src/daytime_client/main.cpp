#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "asio.hpp"

#include <iostream>

using namespace std;
using namespace asio;
using namespace asio::ip;

int main() {
    auto console = spdlog::stderr_color_mt("console");
    console->set_level(spdlog::level::err);
   
    tcp::iostream strm{"localhost", "1113"};

    if (strm) {
        strm << "get-time" << endl;
        string data;
        getline(strm, data);
        cout << data << endl;
        strm.close();
    } else {
        console->error("Could not connect to server!");
    }
}