template <typename T>
Matrix3D<T> Preprocessing::rgb2ycocg(Matrix3D<T> inImg) {
    Matrix3D<T> ycocg(inImg.channel(),inImg.raw(),inImg.col());
    
}

template <typename T>
Matrix3D<T> Preprocessing::ycocg2rgb(Matrix3D<T> inImg) {}

template <typename T>
Matrix3D<T> Preprocessing::rgb2ycbcr(Matrix3D<T> inImg) {}

template <typename T>
Matrix3D<T> Preprocessing::ycbcr2rgb(Matrix3D<T> inImg) {}
