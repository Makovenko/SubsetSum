#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <stdexcept>
#include <utils.h>

class Problem {
private:
  std::vector<std::vector<int>> m_vectors;
  std::vector<int> m_objective;
  int m_k;

public:
  Problem(const std::vector<int>& objective, const int k): m_objective(objective), m_k(k) {}
  Problem(std::vector<int>&& objective, const int k): m_k(k) { std::swap(m_objective, objective); }
  Problem(const Problem& problem): m_k(problem.m_k) {
    m_vectors = problem.m_vectors;
    m_objective = problem.m_objective;
  }
  Problem& operator=(const Problem& other) {
    m_vectors = other.m_vectors;
    m_objective = other.m_objective;
    m_k = other.m_k;
    return *this;
  }
  ~Problem() {}

  inline int N() const { return static_cast<int>(m_vectors.size()); }
  inline int M() const { return static_cast<int>(m_objective.size()); }
  inline int K() const { return m_k; }

  void addVector(const std::vector<int>& vector) {
    if (static_cast<int>(vector.size()) != M()) throw std::runtime_error(
      "Wrong vector dimensions: it should be " + std::to_string(M()) +
      ", while the actual size is " + std::to_string(vector.size())
    );
    m_vectors.emplace_back(vector);
  }

  const std::vector<int>& getVector(const int id) const { return m_vectors.at(id); }
  std::vector<int> vector(const int id) const { return m_vectors.at(id); }

  const std::vector<int>& getObjective() const { return m_objective; }
  std::vector<int> getSlice(const int cord) const {
    std::vector<int> result;
    std::transform(
      m_vectors.begin(), m_vectors.end(), std::back_inserter(result),
      [&cord, this](const std::vector<int>& v){return v[cord];}
    );
    return result;
  }

  friend std::ostream& operator<<(std::ostream& os, const Problem& P);
};

std::ostream& operator<<(std::ostream& os, const Problem& P) {
  os<<"Vectors in pool:"<<std::endl;
  os<<"\t----------------------------------------"<<std::endl;
  for (auto& v: P.m_vectors) os<<"\t"<<v<<std::endl;
  os<<"\t----------------------------------------"<<std::endl;
  os<<"Objective vector:"<<std::endl;
  os<<"\t----------------------------------------"<<std::endl;
  os<<"\t"<<P.m_objective<<std::endl;
  os<<"\t----------------------------------------"<<std::endl;
  return os;
}

#endif // PROBLEM_H
