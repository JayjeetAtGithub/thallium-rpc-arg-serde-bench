#include <iostream>
#include <thallium.hpp>
#include <thallium/serialization/stl/string.hpp>
#include <thallium/serialization/stl/vector.hpp>

namespace tl = thallium;

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <address>" << std::endl;
        exit(0);
    }

    int num_rows = 1000;
    int num_cols = 17;
    std::vector<int> types{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    std::vector<int64_t> data_buff_sizes{14564, 36366, 57755, 44833, 33323, 44445, 55555, 99999, 647474, 34635, 3848, 485757, 47474, 92784, 48489, 29847, 38474};
    std::vector<int64_t> offset_buff_sizes{143564, 31266, 57755, 44233, 33063, 41445, 35255, 99998, 637474, 34335, 38480, 485457, 17474, 72784, 43489, 29347, 38174};;    


    tl::engine myEngine("verbs", THALLIUM_CLIENT_MODE);
    tl::remote_procedure sum = myEngine.define("sum");
    tl::endpoint server = myEngine.lookup(argv[1]);
    int ret = sum.on(server)(num_rows, num_cols, types, data_buff_sizes, offset_buff_sizes);
    std::cout << "Server answered " << ret << std::endl;

    return 0;
}