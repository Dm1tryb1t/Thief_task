#include "struct.hpp"

#include <vector>

unsigned get_max_summary_value_recursive(const std::vector<Valuables>& vals, unsigned max_weight, unsigned cur_value, unsigned cur_weight, int id);

unsigned get_max_summary_value_dynamic(const std::vector<Valuables>& vals, unsigned max_weight);
