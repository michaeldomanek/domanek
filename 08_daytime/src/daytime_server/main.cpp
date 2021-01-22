#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "asio.hpp"

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

int main() {
    auto console = spdlog::stderr_color_mt("console");
    console->set_level(spdlog::level::err);

    io_context ctx;
    tcp::endpoint ep{tcp::v4(), 1113};
    tcp::acceptor acceptor{ctx, ep};
    acceptor.listen();

    while (true) {
        tcp::iostream strm{acceptor.accept()};

        string data;
        strm >> data;
        strm << std::chrono::system_clock::now();
        strm.close(); 
    }
}