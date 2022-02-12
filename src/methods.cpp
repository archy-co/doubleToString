#include <cstddef>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <cstring>
#include <boost/lexical_cast.hpp>
#include <QString>
#include "ryu/ryu.h"
#include "double-conversion/double-to-string.h"


constexpr int maxNumberSize = 128;

// TODO: Fix casts to C++ style

std::pair<size_t, double> method1_stringstream(const std::vector<double> & numbers)
{
    std::pair<size_t, double> res;

    std::stringstream ss;
    ss.precision(9);

    for (auto num : numbers)
        ss << num;

    size_t letter_count = ss.str().size();

    res.first = letter_count;
    res.second = (double) letter_count/numbers.size();
    return res;
}

std::pair<size_t, double> method2_to_string(const std::vector<double> & numbers)
{
    std::pair<size_t, double> res;

    size_t letter_count = 0;
  
    for (auto num : numbers)
    {
        auto curr_str = std::to_string(num);
        letter_count += curr_str.size();
    }
  
    res.first = letter_count;
    res.second = (double) letter_count/numbers.size();
    return res;
}

std::pair<size_t, double> method3_sprintf(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;

    size_t length = 0;
    int counter = 0;
    char str[200];
    for (auto x : numbers) {
        sprintf(str, "%.6f", x);
        length += strlen(str);
        counter++;
    }
    res.first = length;
    res.second = (double)length / counter;

    return res;
}

std::pair<size_t, double> method4_boost(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;

    size_t length = 0;
    int counter = 0;
    std::string str;
    for (auto x: numbers) {
        str = boost::lexical_cast<std::string>(x);
        length += str.size();
        counter++;
    }
    res.first = length;
    res.second = (double)length / counter;

    return res;
}

std::pair<size_t, double> method5_qt(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;

    long long length = 0;
    int counter = 0;
    QString str;
    for (auto x: numbers) {
        str = QString::number(x, 'g', 9);
        length += str.size();
        counter++;
    }
    res.first = length;
    res.second = (double)length / counter;

    return res;
}

std::pair<size_t, double> method6_ryu(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;
    long long length = 0;

    for (auto x: numbers) {
        std::string a_str = d2fixed(x, 6);
        length += a_str.size();
    }

    res.first = length;
    res.second = (double) length / numbers.size();

    return res;
}

std::pair<size_t, double> method7_google(const std::vector<double> & numbers) {
    std::pair<size_t, double> res;
    long long length = 0;

    auto flags = double_conversion::DoubleToStringConverter::NO_FLAGS;
    double_conversion::DoubleToStringConverter dc(flags, NULL, NULL, 'e', -1, 1, 0, 0);

    char str[maxNumberSize];
    double_conversion::StringBuilder builder(str, maxNumberSize);
    builder.Reset();

    for (auto x: numbers) {
        dc.ToFixed(x, 6, &builder);
        char *fstr = builder.Finalize();
        length += strlen(fstr);
        builder.Reset();
    }

    res.first = length;
    res.second = (double) length / numbers.size();

    return res;
}
