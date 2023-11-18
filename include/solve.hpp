#include "struct.hpp"

#include <vector>


void print_vec(const std::vector<unsigned> &vec);

unsigned get_max_summary_value_recursive(const std::vector<Valuables> &vals, unsigned max_weight);

unsigned get_max_summary_value_dynamic(const std::vector<Valuables> &vals, unsigned max_weight, std::vector<unsigned> &my_path);
