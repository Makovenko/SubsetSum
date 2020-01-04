#ifndef FILEREADER_H
#define FILEREADER_H

#include <random>
#include <algorithm>
#include <iostream>
#include <string>
#include "problem.h"
#include "utils.h"

class FileReader {
private:
  const int m_n, m_m, m_k;
  const int m_maxInt;

public:
  FileReader(const int n, const int m, const int k, const int max):
    m_n(n), m_m(m), m_k(k), m_maxInt(max) {}

  Problem readFromFile(std::istream& input) {
    std::vector<int> objective(m_m, 0);
    for (int i = 0; i < m_m; ++i) input >> objective[i];
    std::vector<std::vector<int>> pool;
    for (int i = 0; i < m_n; ++i) {
      pool.emplace_back(std::vector<int>(m_m, 0));
      for (int j = 0; j < m_m; ++j)
        input >> pool.back()[j];
    }

    Problem instance(objective, m_k);
    for (auto& v: pool) instance.addVector(v);
    return instance;
  }
};

#endif // FILEREADER_H
