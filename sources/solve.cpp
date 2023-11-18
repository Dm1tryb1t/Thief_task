#include "../include/solve.hpp"

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::vector<unsigned> path;
// std::set<unsigned> path_recursive;

void find_prev_taken(const std::vector<Valuables> &vals, const std::vector<std::vector<unsigned>> &A, const std::pair<unsigned, unsigned> &ind) {
  if (ind.first * ind.second == 0) {
    return;
  }
  if (A[ind.first][ind.second] == A[ind.first - 1][ind.second]) { // значит, не брали этот предмет
    find_prev_taken(vals, A, std::make_pair(ind.first - 1, ind.second));
    return;
  }
  find_prev_taken(vals, A, std::make_pair(ind.first - 1, ind.second - vals[ind.first - 1].weight));
  path.push_back(ind.first);
}

void find_path(const std::vector<Valuables> &vals, const std::vector<std::vector<unsigned>> &A, unsigned max_weight) {
  find_prev_taken(vals, A, std::make_pair(vals.size(), max_weight));
}

void print_vec(const std::vector<unsigned> &vec) {
  for (const auto el : vec) {
    std::cout << el << ' ';
  }
  std::cout << std::endl;
  // path.clear();
}

unsigned get_max_summary_value_dynamic(const std::vector<Valuables> &vals, unsigned max_weight, std::vector<unsigned> &my_path) {
  std::vector<std::vector<unsigned>> A(vals.size() + 1, std::vector<unsigned>(max_weight + 1));
  for (unsigned i = 1; i < vals.size() + 1; ++i) {
    for (unsigned j = 1; j < std::min(vals[i - 1].weight, max_weight + 1); ++j) {
      A[i][j] = A[i - 1][j]; // когда максимальный вес не позволяет добавить этот предмет
    }
    for (unsigned j = vals[i - 1].weight; j < max_weight + 1; ++j) {
      A[i][j] = std::max(A[i - 1][j], A[i - 1][j - vals[i - 1].weight] + vals[i - 1].value);
    }
  }
  find_path(vals, A, max_weight);
  my_path = path;
  path.clear();
  // print_path();
  return A[vals.size()][max_weight];
}

unsigned get_max_summary_value_recursive_(const std::vector<Valuables> &vals, unsigned max_weight, unsigned cur_value, unsigned cur_weight, int id) {
  if (id == -1) {
    return cur_value;
  }
  unsigned nene = get_max_summary_value_recursive_(vals, max_weight, cur_value, cur_weight, id - 1);
  unsigned dada = 0;
  if (cur_weight >= vals[id].weight) {
    dada = get_max_summary_value_recursive_(vals, max_weight, cur_value + vals[id].value, cur_weight - vals[id].weight, id - 1);
  }
  // тут как-то восстанавливаем путь ещё
  if (dada > nene) {

    return dada;
  }
  return nene;
}

unsigned get_max_summary_value_recursive(const std::vector<Valuables> &vals, unsigned max_weight) {
  unsigned tmp = get_max_summary_value_recursive_(vals, max_weight, 0, max_weight, vals.size() - 1);
  return tmp;
}