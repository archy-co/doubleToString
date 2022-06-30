#include <atomic>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include "methods.hpp"
#include "main.hpp"

/*
 * Arguments:  method# infile outfile
 */
int
main (int argc, char **argv) {

    if (argc < 4)
    {
        std::cerr << "Wrong number of arguments" << std::endl;
        return WRONG_ARGS;
    }

    std::string TIME_RES_FN = ".temp";   // Should be the same as TIME_RES_FN in python script
    // TIME_RES_FN can be passed as fifth argument. Defaults to the line above if not specified
    if (argc == 5)
        TIME_RES_FN = argv[4];

    int method = atoi(argv[1]);
    std::string in_file = argv[2];
    std::string out_file = argv[3];

    std::vector<double> numbers;

    auto r_status = read_numbers(in_file, &numbers);

    if (r_status) {
        std::cerr << "Error writing results" << std::endl;
        return r_status;
    }

    std::pair<size_t, double> res;

    auto start_time = get_current_time_fenced();
    switch (method) {
        case 1:
            res = method1_stringstream(numbers);
            break;
        case 2:
            res = method2_to_string(numbers);
            break;
        case 3:
            res = method3_sprintf(numbers);
            break;
        case 4:
            res = method4_boost(numbers);
            break;
        case 5:
            res = method5_qt(numbers);
            break;
        case 6:
            res = method6_ryu(numbers);
            break;
        case 7:
            res = method7_google(numbers);
            break;
        case 8:
            res = method8_gcvt(numbers);
            break;
        case 9:
            res = method9_ostringstream(numbers);
            break;
        case 10:
            res = method10_strtk(numbers);
            break;
        case 11:
            res = method11_custom(numbers);
            break;
        case 12:
            res = method12_write_to_file(numbers);
            break;
        case 13:
            res = method13_to_wstring(numbers);
            break;
        case 14:
            res = method14_floaxie(numbers);
            break;
       default:
       {
            std::cerr << "Wrong method" << std::endl;
            return WRONG_METHOD;
       }
    }
    auto finish_time = get_current_time_fenced();

    //std::cout << res.first << " " << res.second << std::endl;

    std::ofstream time_res(TIME_RES_FN);
    time_res << to_us(finish_time - start_time);
    time_res << "\n";
    time_res.close();

    auto w_status = write_res(out_file, res);
    if (w_status) {
        std::cerr << "Error writing results" << std::endl;
        return w_status;
    }

    return 0;
}

int read_numbers(const std::string &fn, std::vector<double> *numbers)
{
    std::ifstream file(fn);
    
    if (!file)
    {
        std::cerr << "Error opening in file" << std::endl;
        return ERROR_OPENING_IN_FILE;
    }
    
    double current_word = 0;
    while(file>>current_word)
        (*numbers).push_back(current_word);

    if (!file.eof())
    {
        std::cerr << "Error reading in file" << std::endl;
        return ERROR_READING_IN_FILE;
    }

    return 0;
}

int
write_res (const std::string &fn, std::pair<size_t, double> res)
{
    std::ofstream file(fn);

    if (!file)
    {
        std::cerr << "Error opening out file" << std::endl;
        return ERROR_OPENING_OUT_FILE;
    }

    std::stringstream res_ss;
    res_ss << res.first << "\n" << res.second << "\n";

    file << res_ss.str();
    return 0;
}



template<class D>
inline long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}
