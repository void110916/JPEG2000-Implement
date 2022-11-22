#include <iostream>
#include "bitmap.h"
typedef BMP::BMPWriter BMPWriter;
int main()
{
    BMPWriter Rbmp;
    Rbmp.read("Test_card.bmp");
    auto raw=Rbmp.get();
    BMPWriter Wbmp;
    Wbmp.write(raw,"Test_card_wr.bmp");
    return 0;
}