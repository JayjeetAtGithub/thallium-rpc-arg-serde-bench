#include <iostream>
#include <thallium.hpp>
#include <thallium/serialization/stl/string.hpp>
#include <thallium/serialization/stl/vector.hpp>

namespace tl = thallium;

std::function<void(const tl::request&, int&, int&, std::vector<int>&, std::vector<int64_t>&, std::vector<int64_t>&)> sum =
        [*](const tl::request& req, int& x, int& y, std::vector<int>& types, std::vector<int64_t>& data_buff_sizes, std::vector<int64_t>& offset_buff_sizes) {        
        req.respond(x+y);
    };

std::function<void(const tl::request&, int&, int&)> sum_light =
        [*](const tl::request& req, int& x, int& y) {        
        req.respond(x+y);
    };


int main(int argc, char** argv) {

    tl::engine myEngine("verbs", THALLIUM_SERVER_MODE);
    std::cout << "Server running at address " << myEngine.self() << std::endl;
    myEngine.define("sum", sum);
    myEngine.define("sum_light", sum_light);

    return 0;
}
