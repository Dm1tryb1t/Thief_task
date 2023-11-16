#include "struct.hpp"

#include <vector>

unsigned get_max_summary_value_recursive(const std::vector<Valuables>& vals, int max_weight, int cur_value, int cur_weight, int id);

int get_max_summary_value_dynamic(const std::vector<Valuables>& vals, int max_weight);
