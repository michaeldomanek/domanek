#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace std;

int main() {
    auto console = spdlog::stderr_color_mt("console");
    console->set_level(spdlog::level::trace);
    console->info("Hello World!");
}