#include "preprocessing.h"
#include "matrix.h"
#include <iostream>
using namespace JPEG2000;
int main() {
  Matrix3D<int16_t> rgb(3, 5, 5);
  auto ycocg = Preprocessing::fRCT(rgb);
  for (size_t k = 0; k < 3; k++) {
    for (size_t j = 0; j < 5; j++) {
      for (size_t i = 0; i < 5; i++) {
        std::cout << ycocg[k][j][i] << " ";
      }
      std::cout << "\n";
    }
    std::cout << "\n"<<std::endl;
  }
}