#ifndef SUBSETSUMSCALARDP_H
#define SUBSETSUMSCALARDP_H

#include <vector>
#include <limits>

class SubsetSumScalarDP {
private:
  const int m_K, m_S, m_N;
  std::vector<std::vector<std::vector<int>>> m_dp;
  std::vector<int> m_v;

  int QMin(int k, int s) const {
    if (k == 0 && s == 0) return -1;
    if (s < 0 || s > m_S+1 || k < 0 || m_dp[k][s].empty()) return std::numeric_limits<int>::max();
    return m_dp[k][s].front();
  }

  std::vector<int>& Q(int k, int s) {
    return m_dp[k][s];
  }

  void allocateArrays() {
    m_dp.resize(m_K+1, std::vector<std::vector<int>>(m_S+4, std::vector<int>()));
  }

public:
  SubsetSumScalarDP(int K, const std::vector<int>& values, const int objective):
    m_K(K), m_S(objective), m_N(static_cast<int>(values.size())), m_v(values) {}

  void solve() {
    allocateArrays();
    for (int k = 1; k <= m_K; ++k) {
      for (int s = 0; s <= m_S; ++s) {
        for (int n = 0; n < m_N; ++n) {
          if (QMin(k - 1, s - m_v[n]) < n) {
            m_dp[k][s].emplace_back(n);
          }
        }
      }
    }
  }

  std::vector<std::vector<std::vector<int>>> getCertificate() const {
    return m_dp;
  }
};

#endif // SUBSETSUMSCALARDP_H
