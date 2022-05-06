#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>
#include <chrono>
#include <unistd.h>


const char* executable_name = R"(C:\Users\andre\PycharmProjects\term_paper\WindowsApp\Sorter\Debug\ProcessSorter.exe)";
std::string get_input_file_name(const int order_number) {
    return "input" + std::to_string(order_number) + ".txt";
}

std::string get_output_file_name(const int order_number) {
    return "output" + std::to_string(order_number) + ".txt";
}

void throw_if_io_exception(std::fstream* source,const std::string& file_name) {
    if (!source->good()) {
        std::cout << "Error occured while processing file " << file_name << std::endl;
        throw std::invalid_argument(file_name);
    }
}

void sort_file(const int order_number) {
    const std::string input_file_name = get_input_file_name(order_number),
                      output_file_name = get_output_file_name(order_number);
    
    std::ifstream input("./Tests/" + input_file_name);
    if (!input.is_open()) {
        std::cout << "cannot open file" << std::endl;
    }
    
    std::vector<std::string> string_collection;
    std::string buffer;
    while(std::getline(input, buffer)) {
        string_collection.push_back(buffer);
    }
    input.close();
    
    std::sort(string_collection.begin(), string_collection.end());
    std::ofstream output("./Out/" + output_file_name, std::fstream::out);
    
    copy(string_collection.begin(), string_collection.end(), std::ostream_iterator<std::string>(output, "\n"));
    output.close();
    
}

// NUMBER FILES PROC_COUNT
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "invalid number of parameters, expected 3, got : " << argc << std::endl;
        return -1;
    }
    int new_nice = 1;//nice(-10);
    if (new_nice == -1){
        std::cout << "Sorter_" << argv[1] <<" Error while setting nice value" << std::endl;
        return -1;
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = atoi(argv[1]); i < atoi(argv[2]); i += atoi(argv[3])) {
        sort_file(i);
        std::cout << "Sorter_" << argv[1] << ":: File #" << i << " sorted\n";
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    return 0;
}
