#include "../include/solve.hpp"

#include <vector>


std::vector<int> path;

void find_prev_taken(const std::vector<Valuables>& vals, const std::vector<std::vector<int>>& A, const std::pair<int, int>& ind) {
    if (ind.first * ind.second == 0) {
        return;
    }
    if (A[ind.first][ind.second] == A[ind.first - 1][ind.second]) { // значит, не брали этот предмет
        find_prev_taken(vals, A, std::make_pair(ind.first - 1, ind.second));
        return;
    }
    find_prev_taken(vals, A, std::make_pair(ind.first - 1, ind.second - vals[ind.first].weight));
    path.push_back(ind.first + 1);
}

void find_path(const std::vector<Valuables>& vals, const std::vector<std::vector<int>>& A, int max_weight) {
    find_prev_taken(vals, A, std::make_pair(vals.size(), max_weight));
}

int get_max_summary_value_dynamic(const std::vector<Valuables>& vals, int max_weight) {
    std::vector<std::vector<int>> A(vals.size() + 1, std::vector<int>(max_weight + 1));
    for (int i = 1; i < vals.size() + 1; ++i) {
        for (int j = 1; j < std::min(vals[i].weight + 1, max_weight + 1); ++j) {
            A[i][j] = A[i - 1][j]; // когда максимальный вес не похволяет добавить этот предмет
        }
        for (int j = vals[i].weight + 1; j < max_weight + 1; ++j) {
            A[i][j] = std::max(A[i - 1][j], A[i - 1][j - vals[i].weight] + vals[i].value);
        }
    }
    find_path(vals, A, max_weight);
    return A[vals.size()][max_weight];
}

unsigned get_max_summary_value_recursive(const std::vector<Valuables>& vals, unsigned max_weight, unsigned cur_value, unsigned cur_weight, int id) {
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
