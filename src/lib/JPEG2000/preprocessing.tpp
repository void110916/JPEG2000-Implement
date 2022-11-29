template <typename T>
Matrix3D<T> Preprocessing::fRCT(Matrix3D<T> inImg) {
  Matrix3D<T> ycbcr(inImg.channel(), inImg.height(), inImg.width());
  for (size_t j = 0; j < inImg.height(); j++) {
    for (size_t i = 0; i < inImg.width(); i++) {
      ycbcr[0][j][i] =
          (inImg[0][j][i] + 2 * inImg[1][j][i] + inImg[2][j][i]) / 4;
      ycbcr[2][j][i] = inImg[0][j][i] - inImg[1][j][i];
      ycbcr[1][j][i] = inImg[2][j][i] - inImg[1][j][i];
    }
  }
  return ycbcr;
}

template <typename T>
Matrix3D<T> Preprocessing::iRCT(Matrix3D<T> inImg) {
  Matrix3D<T> rgb(inImg.channel(), inImg.height(), inImg.width());
  for (size_t j = 0; j < inImg.height(); j++) {
    for (size_t i = 0; i < inImg.width(); i++) {
      rgb[1][j][i] = inImg[0][j][i] - (inImg[1][j][i] + inImg[2][j][i]) / 4;

      rgb[0][j][i] = inImg[1][j][i] + rgb[2][j][i];
      rgb[2][j][i] = inImg[1][j][i] + rgb[1][j][i];
    }
  }
  return rgb;
}

template <typename T>
Matrix3D<float> Preprocessing::fICT(Matrix3D<T> inImg) {
  Matrix3D<float> ycbcr(inImg.channel(), inImg.height(), inImg.width());
  for (size_t j = 0; j < inImg.height(); j++) {
    for (size_t i = 0; i < inImg.width(); i++) {
      ycbcr[0][j][i] = 0.299f * inImg[0][j][i] + 0.587f * inImg[1][j][i] +
                       0.114f * inImg[2][j][i];

      ycbcr[1][j][i] = -0.16875 * inImg[0][j][i] -
                       0.331260f * inImg[1][j][i] + 0.500f * inImg[2][j][i];
      ycbcr[2][j][i] = 0.500 * inImg[0][j][i] - 0.41869f * inImg[1][j][i] +
                       0.08131f * inImg[2][j][i];
    }
  }
  return ycbcr;
}

template <typename T>
Matrix3D<float> Preprocessing::iICT(Matrix3D<T> inImg) {
  Matrix3D<float> rgb(inImg.channel(), inImg.height(), inImg.width());

  for (size_t j = 0; j < inImg.height(); j++) {
    for (size_t i = 0; i < inImg.width(); i++) {
      rgb[0][j][i] = inImg[0][j][i] + 1.402f * inImg[2][j][i];

      rgb[1][j][i] = -0.16875 * inImg[0][j][i] -
                     0.331260f * inImg[1][j][i] + 0.500f * inImg[2][j][i];
      rgb[2][j][i] = 0.500 * inImg[0][j][i] - 0.41869f * inImg[1][j][i] +
                     0.08131f * inImg[2][j][i];
    }
  }
  return rgb;
}
