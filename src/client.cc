#include <iostream>
#include <chrono>

#include <thallium.hpp>
#include <thallium/serialization/stl/string.hpp>
#include <thallium/serialization/stl/vector.hpp>

namespace tl = thallium;


class MeasureExecutionTime{
    private:
        const std::chrono::steady_clock::time_point begin;
        const std::string caller;
    public:
        MeasureExecutionTime(const std::string& caller): caller(caller),begin(std::chrono::steady_clock::now()){}
        ~MeasureExecutionTime(){
            const auto duration=std::chrono::steady_clock::now()-begin;
            std::cout <<"client: "<< caller << " : "<<(double)std::chrono::duration_cast<std::chrono::microseconds>(duration).count()/1000<<" ms\n";
        }
};

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <address>" << std::endl;
        exit(0);
    }

    int num_rows = 1000;
    int num_cols = 2;
    std::vector<int> types{1,2};
    std::vector<int64_t> data_buff_sizes{1000, 3000};
    std::vector<int64_t> offset_buff_sizes{5000, 6000};    

    tl::engine myEngine("verbs", THALLIUM_CLIENT_MODE);
    
    tl::remote_procedure sum = myEngine.define("sum");
    tl::remote_procedure sum_light = myEngine.define("sum_light");

    tl::endpoint server = myEngine.lookup(argv[1]);
    {
        MeasureExecutionTime t("sum");
        int ret = sum.on(server)(num_rows, num_cols, types, data_buff_sizes, offset_buff_sizes);
        std::cout << "Server answered " << ret << std::endl;
    }
    {
        MeasureExecutionTime t("sum_light");
        int ret = sum_light.on(server)(num_rows, num_cols);
        std::cout << "Server answered " << ret << std::endl;
    }
    return 0;
}
