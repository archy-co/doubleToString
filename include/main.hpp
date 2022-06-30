#include <chrono>

inline std::chrono::high_resolution_clock::time_point
get_current_time_fenced ();

template<class D>
inline long long
to_us (const D& d);

bool
read_numbers (std::string fn, std::vector<double> *numbers);

bool
write_res (std::string fn, std::pair<size_t, double> res);

enum ERRORS{WRONG_ARGS=1, WRONG_METHOD=2, ERROR_OPENING_IN_FILE=3,
            ERROR_OPENING_OUT_FILE=4, ERROR_READING_IN_FILE=5};