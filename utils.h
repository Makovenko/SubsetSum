#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <vector>
#include <stdexcept>
#include <map>

template<typename T> inline std::ostream& operator<<(std::ostream& s, const std::vector<T>& v) {
  s<<"{";
  for (int i = 0; i < static_cast<int>(v.size()) - 1; ++i) s << v[i] <<", ";
  s<<v.back() <<"}";
  return s;
}

template <typename T> inline std::vector<T>& operator+=(std::vector<T>& left, const std::vector<T>& right) {
  if (left.size() != right.size()) throw std::runtime_error("Vector size mismatch");
  for (int i = 0; i < static_cast<int>(left.size()); ++i) left[i] += right[i];
  return left;
}

template <typename T> inline std::vector<T>& operator-=(std::vector<T>& left, const std::vector<T>& right) {
  if (left.size() != right.size()) throw std::runtime_error("Vector size mismatch");
  for (int i = 0; i < static_cast<int>(left.size()); ++i) left[i] -= right[i];
  return left;
}

struct intWithDef {
  int val = 0;
};

std::vector<int> multisetIntersection(const std::vector<std::vector<int>*>& sets, int max) {
  int s = static_cast<int>(sets.size());
  static int present[1024] = {0};
  std::vector<int> result;
  for (int j = 0; j < static_cast<int>(sets[0]->size()); ++j) {
    present[sets[0]->at(j)] = 1;
  }
  for (int i = 1; i < static_cast<int>(sets.size()); ++i) {
    std::vector<int>* set = sets[i];
    for (int j = 0; j < static_cast<int>(set->size()); ++j)
      ++present[set->at(j)];
  }
  for (int j = 0; j < static_cast<int>(sets[0]->size()); ++j) {
    int val = sets[0]->at(j);
    if (val >= max) break;
    if (present[val] == s) result.push_back(val);
  }
  return result;
 /*
  std::vector<int> result;
  std::map<int, int> present;
  for (int i = 0; i < static_cast<int>(sets.size()); ++i) {
    std::vector<int>& set = *sets[i];
    for (int j = 0; j < static_cast<int>(set.size()); ++j) {
      if (set[j] >= max) break;
      auto it = present.find(set[j]);
      if (it != present.end()) ++present[set[j]];
      else present[set[j]] = 1;
    }
  }
  for (auto v: *(sets[0])) if (present[v] == s) result.push_back(v);
  */
  return result;
}


template <typename T> std::vector<T> operator+(const std::vector<T>& left, const std::vector<T>& right) {
  if (left.size() != right.size()) throw std::runtime_error("Vector size mismatch");
  std::vector<T> result = left;
  for (int i = 0; i < static_cast<int>(left.size()); ++i) result[i] += right[i];
  return result;
}

template <typename T> std::vector<T> operator*(const T left, const std::vector<T>& right) {
  std::vector<T> result = right;
  for (int i = 0; i < static_cast<int>(right.size()); ++i) result[i] *= left;
  return result;
}

template <typename T> std::vector<T> operator*(const std::vector<T>& left, const T right) {
  return right*left;
}

template <typename T> std::vector<T> operator-(const std::vector<T>& left, const std::vector<T>& right) {
  if (left.size() != right.size()) throw std::runtime_error("Vector size mismatch");
  std::vector<T> result = left;
  for (int i = 0; i < static_cast<int>(left.size()); ++i) result[i] -= right[i];
  return result;
}

#endif // UTILS_H
