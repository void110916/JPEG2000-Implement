#ifndef MATRIX_H
#define MATRIX_H
#include <cstdint>
#include <vector>
namespace JPEG2000 {
template <typename T>
class Matrix3D;
template <typename T>
class Matrix {
  /**
   * @brief 
   * referanced by
   * https://stackoverflow.com/questions/1971201/how-to-overload-array-index-operator-for-wrapper-class-of-2d-array/1971207#1971207
   * keyword: nested class
   */
  // referanced by
  // https://stackoverflow.com/questions/1971201/how-to-overload-array-index-operator-for-wrapper-class-of-2d-array/1971207#1971207
  // keyword: 
 protected:
  size_t _current_channel = 0, _raw, _col;
  Matrix3D<T>* M_parent = nullptr;
  T* addr = nullptr;

 private:
  Matrix(Matrix3D<T>* parent, int current_channel)
      : M_parent(parent), _current_channel(current_channel) {}

 public:
  friend Matrix3D<T>;
  Matrix(size_t raw, size_t col, bool zeros = true) : _raw(raw), _col(col) {
    if (zeros)
      addr = new T[raw * col]();
    else
      addr = new T[raw * col];
  }
  Matrix(size_t raw, size_t col, std::vector<uint8_t>& data)
      : _raw(raw), _col(col) {
    addr = std::move(reinterpret_cast<T*>(data.data()));
  }
  ~Matrix() {
    if (M_parent) delete addr;
  }

  class Array {
   private:
    friend class Matrix;
    Array(Matrix& parent, int current_raw)
        : M_parent(parent), _current_raw(current_raw) {}

   public:
    T& operator[](int col) { return M_parent.at(_current_raw, col); }
    const size_t length() { return M_parent._raw; }

   private:
    Matrix& M_parent;
    size_t _current_raw;
  };
  Array operator[](size_t raw) { return Array(*this, raw); }
  virtual T& at(size_t raw, size_t col) {
    return addr ? addr[raw * _col + col]
                : M_parent->at(_current_channel, raw, col);
  }
  const int height() { return _raw; }
  const int width() { return _col; }
};

template <typename T>
class Matrix3D {
 private:
  size_t _channel, _raw, _col;
  T* addr = nullptr;

 public:
  // Matrix3D(size_t channel, size_t raw, size_t col, std::vector<uint8_t>&
  // data)
  //     : _channel(channel) {
  //   M_list.resize;
  // }

  Matrix3D(size_t channel, size_t raw, size_t col, bool zeros = true)
      : _channel(channel), _raw(raw), _col(col) {
    if (zeros)
      addr = new T[channel * raw * col]();
    else
      addr = new T[channel * raw * col];
  }
  ~Matrix3D() { delete addr; }
  Matrix<T> operator[](size_t channel) { return Matrix(this, channel); }
  T& at(size_t channel, size_t raw, size_t col) {
    return addr[channel * _raw * _col + raw * _col + col];
  }
  const int height() { return _raw; }
  const int width() { return _col; }
  const int channel() { return _channel; }
};

// https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
}  // namespace JPEG2000
#endif