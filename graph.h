#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <queue>
#include "problem.h"

static const int sizeN = 128;
static const int sizeK = 9;

class Graph {
  static int edges[sizeN][sizeN][sizeN][sizeK];
  static int newedges[sizeN][sizeN][sizeN][sizeK];
  const int m_N, m_K, m_S;

public:
  Graph(const int n, const int k, const int S, const std::vector<std::vector<std::vector<int>>>& certificate, const std::vector<int>& val);

  void applyDPCertificate(const std::vector<std::vector<std::vector<int>>>& certificate, const std::vector<int>& val, int objective);
  void findWay(const Problem &instance) const;
  bool findWay(std::pair<int, int> from, std::vector<int>& sum, const Problem& instance) const;
};

int Graph::edges[sizeN][sizeN][sizeN][sizeK];
int Graph::newedges[sizeN][sizeN][sizeN][sizeK];

Graph::Graph(const int n, const int k, const int S, const std::vector<std::vector<std::vector<int> > > &certificate, const std::vector<int> &val):
  m_N(n), m_K(k), m_S(S) {
  std::cerr<<"Basis time: setting edges to 0"<<std::endl;
  for (int i = 0; i < sizeN; ++i) {
    for (int k = 0; k < sizeN; ++k) {
      for (int j = 0; j < sizeN; ++j) {
        for (int p = 0; p < sizeK; ++p)
          edges[i][k][j][p] = false;
      }
    }
  }
  std::cerr<<"Basis time: Done."<<std::endl;
  std::cerr<<"Processing the initial certificate."<<std::endl;
  for (int  k = 1; k <= m_K; ++k) {
    std::cerr<<"\tNow at k = "<<k<<std::endl;
    for (int s = 0; s <= m_S; ++s) {
      for (const int& v: certificate[k][s]) {
        if (s - val[v] >= 0) {
          for (const int& u: certificate[k-1][s-val[v]]) {
            if (u < v) edges[v][k][u][k-1] = true;
          }
        }
      }
    }
  }
  std::cerr<<"Done."<<std::endl;
  int cntr = 0;
  for (int i = 0; i < sizeN; ++i) {
    for (int k = 0; k < sizeN; ++k) {
      for (int j = 0; j < sizeN; ++j) {
        for (int p = 0; p < sizeK; ++p)
          if (edges[i][k][j][p]) ++cntr;
      }
    }
  }
  std::cerr<<"Non-zero edges: "<<cntr<<std::endl;
}

void Graph::applyDPCertificate(const std::vector<std::vector<std::vector<int> > > &certificate, const std::vector<int> &val, int objective)
{
  std::cerr<<"Basis time: setting edges to 0"<<std::endl;
  for (int i = 0; i < sizeN; ++i) {
    for (int k = 0; k < sizeN; ++k) {
      for (int j = 0; j < sizeN; ++j) {
        for (int p = 0; p < sizeK; ++p)
          newedges[i][k][j][p] = false;
      }
    }
  }
  std::cerr<<"Basis time: Done."<<std::endl;
  std::cerr<<"Processing the new certificate."<<std::endl;
  for (int  k = 1; k <= m_K; ++k) {
    std::cerr<<"\tNow at k = "<<k<<std::endl;
    for (int s = 0; s <= objective; ++s) {
      for (const int& v: certificate[k][s]) {
        if (s - val[v] >= 0) {
          for (const int& u: certificate[k-1][s-val[v]]) {
            if (u < v && edges[v][k][u][k-1]) newedges[v][k][u][k-1] = true;
          }
        }
      }
    }
  }
  std::cerr<<"Done."<<std::endl;
  std::cerr<<"Basis time: Swapping edges..."<<std::endl;
  for (int i = 0; i < sizeN; ++i) {
    for (int k = 0; k < sizeN; ++k) {
      for (int j = 0; j < sizeN; ++j) {
        for (int p = 0; p < sizeK; ++p)
          edges[i][k][j][p] = newedges[i][k][j][p];
      }
    }
  }
  std::cerr<<"Basis time: Done."<<std::endl;
  int cntr = 0;
  for (int i = 0; i < sizeN; ++i) {
    for (int k = 0; k < sizeN; ++k) {
      for (int j = 0; j < sizeN; ++j) {
        for (int p = 0; p < sizeK; ++p)
          if (edges[i][k][j][p]) ++cntr;
      }
    }
  }
  std::cerr<<"Non-zero edges: "<<cntr<<std::endl;
}

void Graph::findWay(const Problem &instance) const
{
  for (int f = 0; f < m_N; ++f) {
    std::cerr<<"Starting from "<<f<<std::endl;
    std::vector<int> sum = instance.vector(f);
    if (findWay({f, m_K}, sum, instance)) {
      std::cerr<<"\b\b"<<std::endl;
      return;
    }
  }
}

bool Graph::findWay(std::pair<int, int> from, std::vector<int>& sum, const Problem &instance) const
{
  if (from.second == 1 && instance.getObjective() == sum) {
    std::cerr<<"Found way"<<std::endl;
    std::cerr<<from.first<<", ";
    return true;
  }
  for (int t = 0; t < from.first; ++t) {
    if (edges[from.first][from.second][t][from.second - 1]) {
      sum += instance.vector(t);
      if (findWay({t, from.second - 1}, sum, instance)) {
        std::cerr<<from.first<<", ";
        return true;
      }
      sum -= instance.vector(t);
    }
  }
  return false;
}


#endif // GRAPH_H
