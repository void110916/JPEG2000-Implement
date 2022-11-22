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
 protected:
  size_t _current_channel = 0, _raw, _col;
  Matrix3D<T>* M_parent = nullptr;
  std::vector<T> addr;

 private:
  Matrix(Matrix3D<T>* parent, int current_channel)
      : M_parent(parent), _current_channel(current_channel) {}

 public:
  friend Matrix3D<T>;
  Matrix(size_t raw, size_t col) : _raw(raw), _col(col), addr(raw * col) {
    // if (zeros)
    //   addr = new T[raw * col]();
    // else
    //   addr = new T[raw * col];
  }
  Matrix(size_t raw, size_t col, std::vector<uint8_t>& data)
      : _raw(raw), _col(col), addr(std::move(data)) {}

  struct Array {
   private:
    friend class Matrix;
    Array(Matrix& parent, int current_raw)
        : M_parent(parent), _current_raw(current_raw) {}

   public:
    T& operator[](int col) { return M_parent.at(_current_raw, col); }
    size_t length() const { return _raw; }

   private:
    Matrix& M_parent;
    size_t _current_raw;
  };
  Array operator[](size_t raw) { return Array(*this, raw); }
  T& at(size_t raw, size_t col) {
    return M_parent ? M_parent->at(_current_channel, raw, col)
                    : addr[raw * _col + col];
  }
  int height() const { return _raw; }
  int width() const { return _col; }
};

template <typename T>
class Matrix3D {
 private:
  size_t _channel, _raw, _col;

 public:
  std::vector<T> addr;

  Matrix3D(size_t channel, size_t raw, size_t col, bool zeros = true)
      : _channel(channel), _raw(raw), _col(col), addr(channel * raw * col) {
    // if (zeros)
    //   addr = new T[channel * raw * col]();
    // else
    //   addr = new T[channel * raw * col];
  }
  Matrix3D(size_t channel, size_t raw, size_t col, std::vector<T> data)
      : Matrix3D(channel, raw, col, false) {
    addr = std::move(data);
  }

  // Matrix3D(Matrix3D& front)
  //     : _channel(front._channel),
  //       _raw(front._raw),
  //       _col(front._col),
  //       addr(std::move(front.addr)){};

  Matrix3D(Matrix3D&& front) noexcept
      : _channel(front._channel),
        _raw(front._raw),
        _col(front._col),
        addr(std::move(front.addr)){};

  Matrix<T> operator[](size_t channel) { return Matrix(this, channel); }
  T& at(size_t channel, size_t raw, size_t col) {
    return addr[channel * _raw * _col + raw * _col + col];
  }
  int height() const { return _raw; }
  int width() const { return _col; }
  int channel() const { return _channel; }
};

// https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
}  // namespace JPEG2000
#endif