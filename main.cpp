#include <iostream>
#include <fstream>
#include "problem.h"
#include "randomgenerator.h"
#include "filereader.h"
#include "subsetsumscalardp.h"
#include "backtrack.h"
#include "utils.h"

using namespace std;

int main(int argc, char* argv[])
{
  if (argc < 4) {
    std::cerr << "Not enough input parameters" << std::endl;
    return 0;
  }
  int N = std::stoi(argv[1]);
  int M = std::stoi(argv[2]);
  int K = std::stoi(argv[3]);
  int MaxInt = 1000;
  Problem instance({}, 0);
  if (argc == 4) {
    std::cerr<<"Generating random input for N = "<<N<<", M = "<<M<<", K = "<<K<<std::endl;
    RandomInstanceGenerator G(N, M, K, MaxInt);
    instance = G.generate();
  }
  else if (argc == 5) {
    std::string filename = argv[4];
    std::cerr<<"Reading instance from "<<filename<<" for N = "<<N<<", M = "<<M<<", K = "<<K<<std::endl;
    std::ifstream fin(filename);
    FileReader G(N, M, K, MaxInt);
    instance = G.readFromFile(fin);
  }

  std::cout<<instance<<std::endl;
  Backtrack BT(N, M, K);
  for (int i = 0; i < M; ++i) {
    std::cerr<<"Solving DP for coordinate "<<i+1<<std::endl;
    auto slice = instance.getSlice(i);
    auto obj = instance.getObjective()[i];
    SubsetSumScalarDP dp(K, slice, obj);
    dp.solve();
    auto cert = dp.getCertificate();
    std::cerr<<"Done."<<std::endl;
    BT.addCertificate(cert, slice, obj);
  }
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < i; ++j) {
      std::cerr<<"Solving DP for coordinates ("<<i+1<<", "<<j+1<<")"<<std::endl;
      auto slice = instance.getSlice(i)*7 + instance.getSlice(j)*3;
      auto obj   = instance.getObjective()[i]*7 + instance.getObjective()[j]*3;
      SubsetSumScalarDP dp(K, slice, obj);
      dp.solve();
      auto cert = dp.getCertificate();
      std::cerr<<"Done."<<std::endl;
      BT.addCertificate(cert, slice, obj);
    }
  }
  BT.solve(instance);
  return 0;
}
