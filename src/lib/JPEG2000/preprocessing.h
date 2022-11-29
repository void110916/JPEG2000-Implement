#ifndef PREPROCESSING_H
#define PREPROCESSING_H
#include "matrix.h"
namespace JPEG2000 {
class Preprocessing {
 private:
 public:
 /**
  * @brief reversible color transform, only available with 5/3 filter
  *   return [Y, Cb, Cr]
  * @tparam T 
  * @param inImg 
  * @return Matrix3D<T>& 
  */
  template <typename T>
  static Matrix3D<T> fRCT(Matrix3D<T> inImg);
  /**
   * @brief 
   * 
   * @tparam T 
   * @param inImg 
   * @return Matrix3D<T> 
   */
  template <typename T>
  static Matrix3D<T> iRCT(Matrix3D<T> inImg);
  /**
   * @brief irreversible color transform, only available with 9/7 filter
   *  return [Y, Cb, Cr]
   * @tparam T 
   * @param inImg 
   * @return Matrix3D<T>& 
   */
  template <typename T>
  static Matrix3D<float> fICT(Matrix3D<T> inImg);
  template <typename T>
  static Matrix3D<float> iICT(Matrix3D<T> inImg);

};
#include "preprocessing.tpp"
}  // namespace JPEG2000

#endif