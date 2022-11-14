#ifndef MATRIX_H
#define MATRIX_H
#include <cstdint>
#include <vector>
namespace JPEG2000 {
template <typename T>
class Matrix {
  // referanced by
  // https://stackoverflow.com/questions/1971201/how-to-overload-array-index-operator-for-wrapper-class-of-2d-array/1971207#1971207
 private:
  int _raw, _col;
  T* addr;

 public:
  Matrix(int raw, int col);
  ~Matrix();

  class Array {
   private:
    friend class Matrix;
    Array(Matrix& parent, int current_raw)
        : M_parent(parent), _current_raw(current_raw) {}

   public:
    T& operator[](int col) { return M_parent.at(_current_raw, col); }

   private:
    Matrix& M_parent;
    int _current_raw;
  };
  Array operator[](int raw) { return Array(*this, raw); }
  T& at(int raw, int col);
  const int height() { return _raw; }
  const int width() { return _col; }
};
// https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
#include "matrix.tpp"
}  // namespace JPEG2000
#endif