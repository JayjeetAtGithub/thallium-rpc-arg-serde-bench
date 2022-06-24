#include <iostream>
#include <thallium.hpp>

namespace tl = thallium;

void sum(const tl::request& req, int a, int b, std::vector<int> c, std::vector<int64_t> d, std::vector<int64_t> e) {
    std::cout << "Computing " << x << "+" << y << std::endl;
    req.respond(x+y);
}

int main(int argc, char** argv) {

    tl::engine myEngine("verbs", THALLIUM_SERVER_MODE);
    std::cout << "Server running at address " << myEngine.self() << std::endl;
    myEngine.define("sum", sum);

    return 0;
}
