#include <iostream>

#include "matrix.h"
using namespace JPEG2000;
int main() {
  Matrix3D<int> m(3, 5, 5);
  auto l = m[5];
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 5; i++) {
      auto c=m[j][i][i];
      m[j][i][i] = i + j + 1;
    }
  }

  std::cout << "start" << std::endl;
  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        std::cout << m[k][i][j] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << "\n"<<std::endl;
  }
  return 0;
}