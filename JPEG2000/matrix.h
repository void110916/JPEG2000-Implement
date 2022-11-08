#include <cstdint>
#include <vector>
namespace JPEG2000 {
template <typename T>
class Matrix {
 private:
  uint32_t _raw, _col;
  std::vector<T> addr;

 public:
  Matrix(uint32_t raw, uint32_t col);
  ~Matrix();
};
}  // namespace JPEG2000
