#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "asio.hpp"

#include "CLI11.hpp"

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace asio;
using namespace asio::ip;

// from timeutils.h by Günter Kolousek, 2016
inline tcp::iostream& operator<<(tcp::iostream& out, decltype(std::chrono::system_clock::now()) time) {
    time_t t{std::chrono::system_clock::to_time_t(time)};
    out << put_time(localtime(&t), "%Y-%m-%d %H:%M:%S");
    return out;
}

int main(int argc, char* argv[]) {
    CLI::App app("Daytime Server");

    unsigned short port{1113};
    app.add_option("-p,--port", port, "port to connect to");

    CLI11_PARSE(app, argc, argv);

    auto console = spdlog::stderr_color_mt("console");
    console->set_level(spdlog::level::err);

    try {
        io_context ctx;
        tcp::endpoint ep{tcp::v4(), port};
        tcp::acceptor acceptor{ctx, ep};
        acceptor.listen();
    
        while (true) {
            tcp::iostream strm{acceptor.accept()};

            string data;
            strm >> data;
            strm << std::chrono::system_clock::now();
            strm.close(); 
        }
    } catch (asio::system_error& e) {
        console->error(e.what());
    }
}