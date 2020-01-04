#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <vector>
#include <algorithm>
#include <numeric>
#include "utils.h"
#include "problem.h"

class Backtrack {
private:
  std::vector<std::vector<std::vector<std::vector<int>>>> m_certificates;
  std::vector<std::vector<int>> m_values;
  std::vector<int> m_objective;
  std::vector<int> m_solution;
  const int m_N, m_M, m_K;

public:
  Backtrack(int N, int M, int K): m_N(N), m_M(M), m_K(K) {}

  void addCertificate(
    const std::vector<std::vector<std::vector<int>>> &certificate,
    const std::vector<int> &val, int objective
  ) {
    m_certificates.push_back(certificate);
    m_values.push_back(val);
    m_objective.push_back(objective);
  }

  bool solve(const std::vector<int>& objective, int k, const Problem& instance, int max) {
    if (k == 0 && std::accumulate(objective.begin(), objective.end(), 0) == 0) {
      std::cerr<<m_solution<<std::endl;
      m_solution.pop_back();
      return true;
    }

    for (int i = 0; i < static_cast<int>(m_certificates.size()); ++i) if (objective[i] < 0) {
      m_solution.pop_back();
      return false;
    }

    std::vector<std::vector<int>*> toIntersect(static_cast<int>(m_certificates.size()), nullptr);
    for (int i = 0; i < static_cast<int>(m_certificates.size()); ++i)
      toIntersect[i] = &(m_certificates[i][k][objective[i]]);
    auto intersection = multisetIntersection(toIntersect, max);
    for (auto v: intersection) {
      std::vector<int> vec = instance.getVector(v);
      for (int i = 0; i < m_M; ++i) {
        for (int j = 0; j < i; ++j) {
          vec.push_back(vec[i]*7 + vec[j]*3);
        }
      }
      m_solution.push_back(v);
      solve(objective - vec, k-1, instance, v);
    }
    m_solution.pop_back();
    return false;
  }

  void solve(const Problem& instance) {
    solve(m_objective, m_K, instance, m_N+1);
    std::cerr<<std::endl;
  }
};

#endif // BACKTRACK_H
