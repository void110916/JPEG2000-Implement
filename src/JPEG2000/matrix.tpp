
template <typename T>
Matrix<T>::Matrix(int raw, int col) : _raw(raw), _col(col) {
  addr = new T[raw * col]();
}

template <typename T>
Matrix<T>::~Matrix() {
  delete addr;
}
template <typename T>
T& Matrix<T>::at(int raw, int col) {
  return addr[raw * _col + col];
}