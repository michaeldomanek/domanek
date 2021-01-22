#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <asio.hpp>
#include <iostream>

using namespace std;
using namespace asio;
using namespace asio::ip;

int main() {
    // auto console = spdlog::stderr_color_mt("console");
    // console->set_level(spdlog::level::trace);
    // console->info("Hello World!");

    asio::io_context ctx;
    tcp::resolver resolver{ctx};
    
    // try {
        
    auto results = resolver.resolve("localhost", "1113");
    tcp::socket sock{ctx};
    connect(sock, results);

    char reply[28];
    read(sock, buffer(reply, 28));
    cout.write(reply, 28);
    cout << "\n";


    // } catch (system_error& e) {
    //     cerr << e.what() << endl;
    // }   
}