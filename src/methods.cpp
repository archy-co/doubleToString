#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <boost/lexical_cast.hpp>
#include <QString>
#include <charconv>
#include "strtk/strtk.hpp"
#include "ryu/ryu.h"
#include "double-conversion/double-to-string.h"
#include "custom.hpp"
#include "floaxie/ftoa.h"
        
constexpr int MAX_NUMBER_SIZE = 128;
constexpr int ERROR_WORKING_WITH_TEMP_FILE = 7;

std::pair<size_t, double> method1_stringstream(const std::vector<double> & numbers)
{
    std::pair<size_t, double> res;

    std::stringstream ss;
    ss.precision(9);

    for (const auto& num : numbers)
        ss << num;

    size_t letter_count = ss.str().size();

    res.first = letter_count;
    res.second = static_cast<double> (letter_count) / numbers.size();
    return res;
}

std::pair<size_t, double> method2_to_string(const std::vector<double> & numbers)
{
    std::pair<size_t, double> res;

    size_t letter_count = 0;
  
    for (const auto& num : numbers)
    {
        auto curr_str = std::to_string(num);
        letter_count += curr_str.size();
    }
  
    res.first = letter_count;
    res.second = static_cast<double> (letter_count) / numbers.size();
    return res;
}

std::pair<size_t, double> method3_sprintf(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;

    size_t length = 0;
    int counter = 0;
    char str[200];
    for (const auto& x : numbers) {
        sprintf(str, "%.6f", x);
        length += strlen(str);
        counter++;
    }
    res.first = length;
    res.second = static_cast<double>(length) / counter;

    return res;
}

std::pair<size_t, double> method4_boost(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;

    size_t length = 0;
    int counter = 0;
    std::string str;
    for (const auto& x: numbers) {
        str = boost::lexical_cast<std::string>(x);
        length += str.size();
        counter++;
    }
    res.first = length;
    res.second = static_cast<double>(length) / counter;

    return res;
}

std::pair<size_t, double> method5_qt(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;

    long long length = 0;
    int counter = 0;
    QString str;
    for (const auto& x: numbers) {
        str = QString::number(x, 'g', 9);
        length += str.size();
        counter++;
    }
    res.first = length;
    res.second = static_cast<double>(length) / counter;

    return res;
}

std::pair<size_t, double> method6_ryu(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;
    long long length = 0;

    for (const auto& x: numbers) {
        std::string a_str = d2fixed(x, 6);
        length += a_str.size();
    }

    res.first = length;
    res.second = static_cast<double> (length) / numbers.size();

    return res;
}

std::pair<size_t, double> method7_google(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;
    long long length = 0;

    auto flags = double_conversion::DoubleToStringConverter::NO_FLAGS;
    double_conversion::DoubleToStringConverter dc(flags, NULL, NULL, 'e', -1, 1, 0, 0);

    char str[MAX_NUMBER_SIZE];
    double_conversion::StringBuilder builder(str, MAX_NUMBER_SIZE);
    builder.Reset();

    for (const auto& x: numbers) {
        dc.ToFixed(x, 6, &builder);
        char *fstr = builder.Finalize();
        length += strlen(fstr);
        builder.Reset();
    }

    res.first = length;
    res.second = static_cast<double> (length) / numbers.size();

    return res;
}

std::pair<size_t, double> method8_gcvt(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;
    long long length = 0;

    char str[MAX_NUMBER_SIZE];

    for (const auto& x: numbers) {
        gcvt(x, 9, str);
        length += strlen(str);
    }

    res.first = length;
    res.second = static_cast<double> (length) / numbers.size();

    return res;
}

std::pair<size_t, double> method9_ostringstream(const std::vector<double> & numbers)
{
    std::pair<size_t, double> res;

    std::ostringstream oss;
    oss.precision(9);

    for (const auto& num : numbers)
        oss << num;

    size_t letter_count = oss.str().size();

    res.first = letter_count;
    res.second = static_cast<double> (letter_count) / numbers.size();
    return res;
}

std::pair<size_t, double> method10_strtk(const std::vector<double> & numbers)
{
    std::pair<size_t, double> res;
    long long length = 0;

    for (const auto& num : numbers)
    {
        std::string str = strtk::type_to_string<double>(num);
        length += str.size();
    }

    res.first = length;
    res.second = static_cast<double> (length) / numbers.size();
    return res;
}

std::pair<size_t, double> method11_custom(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;
    long long length = 0;

    char str[MAX_NUMBER_SIZE];

    for (const auto& x: numbers) {
        double_to_string(x, str);
        length += strlen(str);
    }

    res.first = length;
    res.second = static_cast<double> (length) / numbers.size();

    return res;
}

std::pair<size_t, double> method12_write_to_file(const std::vector<double> & numbers)
{
    char fn[] = ".temp_conv";

    std::ofstream ofile;
    ofile.open(fn);
    ofile.clear();
    ofile.close();
    if (ofile.fail())
        throw std::ios_base::failure("Error initializing temporary file in method 12");

    std::ifstream ifile;

    std::pair<size_t, double> res;
    long long length = 0;

    for (const auto& x: numbers) {
        ofile.open(fn);
        ofile << x;
        ofile.close();
        if (ofile.fail())
            throw std::ios_base::failure("Failed writing to temporary file in method 12");

        std::string str;

        ifile.open(fn);
        ifile >> str; 
        ifile.close();

        if (ifile.fail())
            throw std::ios_base::failure("Failed reading from temporary file in method 12");

        length += str.size();
    }
    res.first = length;
    res.second = static_cast<double> (length) / numbers.size();

    int status_ = remove(fn);
    if (status_)
        throw std::ios_base::failure("Failed to delete temporary file in method 12");

    return res;
}

std::pair<size_t, double> method13_to_wstring(const std::vector<double> & numbers)
{
    std::pair<size_t, double> res;

    size_t letter_count = 0;
  
    for (const auto& num : numbers)
    {
        auto curr_str = std::to_wstring(num);
        letter_count += curr_str.size();
    }
  
    res.first = letter_count;
    res.second = (double) letter_count/numbers.size();
    return res;
}

std::pair<size_t, double> method14_floaxie(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;
    long long length = 0;

    char str[MAX_NUMBER_SIZE];

    for (const auto& x: numbers) {
        floaxie::ftoa(x, str);
        length += strlen(str);
    }

    res.first = length;
    res.second = static_cast<double> (length) / numbers.size();

    return res;
}
