#ifndef PREPROCESSING_H
#define PREPROCESSING_H
#include "matrix.h"
namespace JPEG2000 {
class Preprocessing {
 private:
 public:
 /**
  * @brief reversible color transform, only available with 5/3 filter
  * 
  * @tparam T 
  * @param inImg 
  * @return Matrix3D<T>& 
  */
  template <typename T>
  static Matrix3D<T> rgb2ycocg(Matrix3D<T> inImg);
  template <typename T>
  static Matrix3D<T> ycocg2rgb(Matrix3D<T> inImg);
  /**
   * @brief irreversible color transform, only available with 9/7 filter
   * 
   * @tparam T 
   * @param inImg 
   * @return Matrix3D<T>& 
   */
  template <typename T>
  static Matrix3D<T> rgb2ycbcr(Matrix3D<T> inImg);
  template <typename T>
  static Matrix3D<T> ycbcr2rgb(Matrix3D<T> inImg);

};
#include "preprocessing.tpp"
}  // namespace JPEG2000

#endif