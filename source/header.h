#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <vector>

struct Valuables 
{
  unsigned value;
  unsigned weight;
};


void print_vec(const std::vector<unsigned> &vec);
unsigned get_max_summary_value_dynamic(const std::vector<Valuables> &vals, unsigned max_weight, std::vector<unsigned> &my_path);

#endif // SORTING_H_INCLUDED