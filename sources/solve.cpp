#include "../include/solve.hpp"

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::vector<unsigned> path;

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
  return A[vals.size()][max_weight];
}