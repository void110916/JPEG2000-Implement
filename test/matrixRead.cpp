#include <string>
#include <iostream>
#include "matrix.h"
#include "wavelet.h"

using namespace std::string_literals;
// using namespace JPEG2000;
int main() {
  JPEG2000::Matrix<uint16_t> m(5, 5);
  for (int i = 0; i < 5; i++) {
    m[i][i] = i + 1;
  }
    std::cout<<"start"<<std::endl;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
        std::cout<<m[i][j]<<" ";
    }
    std::cout<< std::endl;
  }
  return 0;
}