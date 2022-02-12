#ifndef MYCAT_CONFIG_FILE_H
#define MYCAT_CONFIG_FILE_H

#include <boost/program_options.hpp>
#include <string>
#include <exception>
#include <stdexcept>

class OptionsParseException : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

void assert_file_exist(const std::string &f_name);

class command_line_options_t {
public:
    command_line_options_t();
    command_line_options_t(int ac, char **av);

    //! Explicit is better than implicit:
    command_line_options_t(const command_line_options_t&) = default;
    command_line_options_t& operator=(const command_line_options_t&) = delete;
    command_line_options_t(command_line_options_t&&) = default;
    command_line_options_t& operator=(command_line_options_t&&) = delete;
    ~command_line_options_t() = default;

    [[nodiscard]] std::vector<std::string> get_filenames() const { return filenames; };
    [[nodiscard]] bool get_A_flag() const { return A_flag; };

    void parse(int ac, char **av);
private:
    bool A_flag = false;
    std::vector<std::string> filenames;

    boost::program_options::variables_map var_map{};
    boost::program_options::options_description opt_conf{
            "Config File Options:\n\tmycat [-h|--help] [-A_flag] <file1> <file2> ... <fileN>\n"};
};

#endif //MYCAT_CONFIG_FILE_H

