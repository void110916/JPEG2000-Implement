#include "matrix.h"
namespace JPEG2000 {
template<typename T>
Matrix<T>::Matrix(int raw, int col) : _raw(raw), _col(col) {
  addr=new T[raw * col]();
}

template<typename T>
Matrix<T>::~Matrix() {}
template<typename T>
T& Matrix<T>::at(int raw,int col){return addr[raw*_col+col];}

}  // namespace JPEG2000
