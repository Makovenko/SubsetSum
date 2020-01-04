#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>
#include <algorithm>
#include "problem.h"
#include "utils.h"

template <typename T> std::vector<T> vsum(const std::vector<T>& left, const std::vector<T>& right) {
  if (left.size() != right.size()) throw std::runtime_error("Vector size mismatch");
  std::vector<T> result = left;
  for (int i = 0; i < static_cast<int>(left.size()); ++i) result[i] += right[i];
  return result;
}

class RandomInstanceGenerator {
private:
  const int m_n, m_m, m_k;
  const int m_maxInt;
  std::default_random_engine m_randomEngine;

public:
  RandomInstanceGenerator(const int n, const int m, const int k, const int max):
    m_n(n), m_m(m), m_k(k), m_maxInt(max), m_randomEngine(0) {}

  Problem generate() {
    std::uniform_int_distribution<int> dist(0,m_maxInt);
    auto random = [&dist, this](){ return dist(m_randomEngine); };
    auto randomVector = [&random, this] () {
      std::vector<int> res;
      std::generate_n(std::back_inserter(res), m_m, random);
      return res;
    };
    std::vector<std::vector<int>> pool;
    std::generate_n(std::back_inserter(pool), m_n, randomVector);
    auto objective = std::accumulate(pool.begin(), pool.begin()+m_k, std::vector<int>(m_m, 0), vsum<int>);
    std::random_shuffle(pool.begin(), pool.end());
    Problem instance(objective, m_k);
    for (auto& v: pool) instance.addVector(v);
    return instance;
  }
};

#endif // RANDOMGENERATOR_H
