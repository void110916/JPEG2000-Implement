#include "matrix.h"
namespace JPEG2000 {
template<typename T>
Matrix<T>::Matrix(uint32_t raw, uint32_t col) : _raw(raw), _col(col) {
  addr.resize(raw * col);
}

template<typename T>
Matrix<T>::~Matrix() {}
}  // namespace JPEG2000
