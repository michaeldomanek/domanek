#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "asio.hpp"

#include "CLI11.hpp"

#include <iostream>
#include <string>

using namespace std;
using namespace asio;
using namespace asio::ip;

int main(int argc, char* argv[]) {
    CLI::App app("Daytime Client");

    string port{"1113"};
    app.add_option("-p,--port", port, "port to connect to");

    CLI11_PARSE(app, argc, argv);

    auto console = spdlog::stderr_color_mt("console");
    console->set_level(spdlog::level::err);
   
    tcp::iostream strm{"localhost", port};

    try {
        if (strm) {
            strm << "get-time" << endl;
            string data;
            getline(strm, data);
            cout << data << endl;
            strm.close();
        } else {
            console->error("Could not connect to server!");
        }
    } catch (asio::system_error& e) {
        console->error(e.what());
    } 
}