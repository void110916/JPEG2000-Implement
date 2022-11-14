#ifndef PREPROCESSING_H
#define PREPROCESSING_H

namespace JPEG2000 {
class Preprocessing {
 private:
 public:
 /**
  * @brief irreversible color transform, only available with 9/7 filter
  * 
  * @tparam T 
  * @param inImg 
  * @return Matrix<T>& 
  */
  template <typename T>
  static Matrix<T>& rgb2ycocg(Matrix<T> inImg);
  template <typename T>
  static Matrix<T>& ycocg2rgb(Matrix<T> inImg);
  /**
   * @brief reversible color transform, only available with 5/3 filter
   * 
   * @tparam T 
   * @param inImg 
   * @return Matrix<T>& 
   */
  template <typename T>
  static Matrix<T>& rgb2ycbcr(Matrix<T> inImg);
  template <typename T>
  static Matrix<T>& ycbcr2rgb(Matrix<T> inImg);

};

}  // namespace JPEG2000

#endif