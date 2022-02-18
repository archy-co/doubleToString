#include <cstddef>
#include <utility>
#include <vector>

std::pair<size_t, double> method1_stringstream(const std::vector<double> & numbers);
std::pair<size_t, double> method2_to_string(const std::vector<double> & numbers);
std::pair<size_t, double> method3_sprintf(const std::vector<double> & numbers);
std::pair<size_t, double> method4_boost(const std::vector<double> & numbers);
std::pair<size_t, double> method5_qt(const std::vector<double> & numbers);
std::pair<size_t, double> method6_ryu(const std::vector<double> & numbers);
std::pair<size_t, double> method7_google(const std::vector<double> & numbers);
std::pair<size_t, double> method8_gcvt(const std::vector<double> & numbers);
std::pair<size_t, double> method9_ostringstream(const std::vector<double> & numbers);
std::pair<size_t, double> method10_strtk(const std::vector<double> & numbers);
std::pair<size_t, double> method11_custom(const std::vector<double> & numbers);
std::pair<size_t, double> method12_write_to_file(const std::vector<double> & numbers);
//std::pair<size_t, double> method13_charconv(const std::vector<double> & numbers);
