#include <iostream>
#include "bitmap.h"
typedef BMP::BMPWriter BMPWriter;
int main()
{
    BMPWriter bmp;
    bmp.read("img/dinor.png");
}