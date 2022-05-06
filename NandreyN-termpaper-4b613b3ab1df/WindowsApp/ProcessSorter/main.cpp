#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>
#include <chrono>
#include <deque>

enum Strategy {REGULAR, MERGE};
const int LINES_READ_LIMIT = 20000;

std::string get_input_file_name(const int order_number) {
    return "Tests//input" + std::to_string(order_number) + ".txt";
}

std::string get_output_file_name(const int order_number) {
    return "Out//output" + std::to_string(order_number) + ".txt";
}

void throw_if_io_exception(std::fstream* source,const std::string& file_name) {
    if (!source->good()) {
        std::cout << "Error occured while processing file " << file_name << std::endl;
        throw std::invalid_argument(file_name);
    }
}

void sort_file_merging(const int order_number) {
    const std::string input_file_name = get_input_file_name(order_number),
        output_file_name = get_output_file_name(order_number);

    std::ifstream input(input_file_name);
    if (!input.is_open()) {
        std::cout << "cannot open file" << std::endl;
    }

    auto glob_holder = std::vector<std::string>();
    int last_elem = 0;

    std::string buffer;
    bool continue_reading = true;

    while  (continue_reading) {
        for (int i = 0; i < LINES_READ_LIMIT; ++i) {
            std::getline(input, buffer);
            if (input.eof()) {
                continue_reading = false;
                break;
            }
            glob_holder.push_back(buffer);
        }
        // Sort part and merge
        std::sort(glob_holder.begin() + last_elem, glob_holder.end());
        std::inplace_merge(glob_holder.begin(), glob_holder.begin() + last_elem, glob_holder.end());
        last_elem = glob_holder.size() - 1;
    }

    std::ofstream output(output_file_name, std::fstream::out);

    copy(glob_holder.begin(), glob_holder.end(), std::ostream_iterator<std::string>(output, "\n"));
    output.close();
}


void sort_file(const int order_number) {
    const std::string input_file_name = get_input_file_name(order_number),
                      output_file_name = get_output_file_name(order_number);
    
    std::ifstream input(input_file_name);
    if (!input.is_open()) {
        std::cout << "Cannot open file" << std::endl;
        return;
    }
    
    std::vector<std::string> string_collection; 
    //std::deque<std::string> string_collection;
    std::string buffer;
    while(std::getline(input, buffer)) {
        string_collection.push_back(buffer);
    }

    input.close();
    
    std::sort(string_collection.begin(), string_collection.end());
    std::ofstream output(output_file_name, std::fstream::out);
    
    copy(string_collection.begin(), string_collection.end(), std::ostream_iterator<std::string>(output, "\n"));
    output.close();
    if (output.is_open()) {
        std::cout << "Cannot close file" << std::endl;
    }
}

// NUMBER FILES COUNT USE_STRATEGY
int main(int argc, char* argv[]) {
    if (argc < 4 || argc > 5) {
        std::cout << "invalid number of parameters, expected 3, got : " << argv << std::endl;
        return -1;
    }
    const Strategy strat = argc == 5 && atoi(argv[4]) == 1 ? MERGE : REGULAR;

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = atoi(argv[1]); i < atoi(argv[2]); i += atoi(argv[3])) {
        switch (strat) {
            case REGULAR:
                sort_file(i);
                break;
            case MERGE:
                sort_file_merging(i);
                break;
            default:
                return -444;
        }

        std::cout << "Sorter_" << argv[1] << ":: File #" << i << " sorted\n";
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    return 0;
}