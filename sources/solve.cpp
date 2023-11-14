#include "../include/solve.hpp"

#include <vector>

unsigned get_max_summary_value(const std::vector<Valuables>& vals, unsigned max_weight, unsigned cur_value, unsigned cur_weight, int id) {
  if (id == -1) {
    return cur_value;
  }
  unsigned nene = get_max_summary_value(vals, max_weight, cur_value, cur_weight, id - 1);
  unsigned dada = 0;
  if (cur_weight >= vals[id].weight) {
    dada = get_max_summary_value(vals, max_weight, cur_value + vals[id].value, cur_weight - vals[id].weight, id - 1);
  }
  // тут как-то восстанавливаем путь ещё
  if (dada > nene) {
    
    return dada;
  }
  return nene;
}
