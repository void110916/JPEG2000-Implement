#ifndef BITMAP_H
#define BITMAP_H
#include <array>
#include <fstream>
#include <string>
#include <vector>

#include "matrix.h"
// reference by:
// https://github.com/yangcha/bmpmini/blob/master/bmpmini.hpp
namespace BMP {
#pragma pack(push, 1)  // alignment to one bit
struct BMPHeader {
  uint16_t magic_number{0x4D42};  // magic number: BM
  uint32_t file_size{0};          // in bytes
  uint16_t reserved1{0};          // Reserved
  uint16_t reserved2{0};          // Reserved
  uint32_t offset_data{54};  // Offset of byte where bitmap image data starts

  // BMP information header
  uint32_t header_size{40};  // size of this header, in bytes (40)
  int32_t width{0};          // width in pixels (signed integer)
  int32_t height{0};   // height in pixels (signed integer, positive- bottom-up,
                       // negative- top-down)
  uint16_t planes{1};  // number of color planes (must be 1)
  uint16_t bit_per_pixel{24};  // number of bits per pixel. Typical values are
                               // 1, 4, 8, 16, 24 and 32
  uint32_t compression_method{0};  // compression method: 3 - BITFIELD.
  uint32_t image_size{
      0};  // size of the raw bitmap data in bytes, 0 - uncompressed images
  int32_t h_pixels_per_meter{2835};  // horizontal resolution of the image
  int32_t v_pixels_per_meter{2835};  // vertical resolution of the image
  uint32_t colors_in_palette{
      0};  // number of colors in the color palette. Use 0 for the max number of
           // colors allowed by bit_count
  uint32_t important_colors{0};  // number of important colors used, or 0 when
                                 // every color is important; generally ignored
};
#pragma pach(pop)

struct BitField {
  uint32_t red{0x00ff0000U};
  uint32_t green{0x0000ff00U};
  uint32_t blue{0x000000ffU};
  uint32_t alpha{0xff000000U};
};

struct ColorPalette {
  constexpr ColorPalette() : table{0} {
    for (auto i = 1; i < 256; i++) table[i] = table[i - 1] + 0x00010101u;
  }
  uint32_t table[256];
};
class BMPWriter {
 private:
  BMPHeader header;
  bool is8bit() const { return header.bit_per_pixel == 8; }
  uint32_t paddedRowSize() const {
    return ((header.width * header.bit_per_pixel + 31U) / 32U) *
           sizeof(uint32_t);
  }
  std::vector<uint8_t> pixel_data;
  std::vector<uint8_t> RGBconvert32(uint32_t RMask, uint32_t GMask,
                                    uint32_t BMask) {
    std::vector<uint8_t> rgbRaw(3 * header.height * header.width);
    std::array<uint32_t, 3> masks{RMask, GMask, BMask};
    uint8_t* raw_ptr = rgbRaw.data();
    uint32_t* pixel_ptr = reinterpret_cast<uint32_t*>(pixel_data.data());
    for (int j = 0; j < 3; j++) {
      for (uint32_t i = 0; i < header.height * header.width;
           i++, raw_ptr++, pixel_ptr++) {
        *raw_ptr = (*pixel_ptr & masks[j]) >> ((2 - j) * 8);
      }
      pixel_ptr = reinterpret_cast<uint32_t*>(pixel_data.data());
    }
    return rgbRaw;
  }
  std::vector<uint8_t> RGBconvert24() {
    if (header.compression_method != 0)
      std::invalid_argument(
          "Bits Per Pixel 24 invalid convet when compression is not 0");
    std::vector<uint8_t> rgbRaw(3 * header.height * header.width);
    uint8_t* raw_ptr = rgbRaw.data();
    uint8_t* pixel_ptr = pixel_data.data();
    for (int j = 0; j < 3; ) {
      for (uint32_t i = 0; i < header.height * header.width;
           i++, raw_ptr++, pixel_ptr += 3) {
        *raw_ptr = *pixel_ptr;
      }
      pixel_ptr = pixel_data.data() + ++j;
    }
    return rgbRaw;
  }
  void iRGBconvert32(const std::vector<uint8_t>& rgbRaw) {
    auto padded_row_size = paddedRowSize();
    pixel_data.resize(header.height * padded_row_size);
    // auto s=rgbRaw.size();
    // std::array<uint32_t, 3> masks{RMask, GMask, BMask};
    const uint8_t* raw_ptr = rgbRaw.data();
    // uint8_t* end=&*rgbRaw.end();
    uint32_t* pixel_ptr = reinterpret_cast<uint32_t*>(pixel_data.data());
    for (int j = 0; j < 3; j++) {
      for (uint32_t i = 0; i < header.height * header.width;
           i++, pixel_ptr++, raw_ptr++) {
        if (j == 0) *pixel_ptr |= 0xff000000U;
        *pixel_ptr |= *raw_ptr << ((2 - j) * 8);
      }
      pixel_ptr = reinterpret_cast<uint32_t*>(pixel_data.data());
    }
  }
  void iRGBconvert24(const std::vector<uint8_t>& rgbRaw) {
    auto padded_row_size = paddedRowSize();
    pixel_data.resize(header.height * padded_row_size);
    const uint8_t* raw_ptr = rgbRaw.data();
    // uint8_t* end=&*rgbRaw.end();
    uint8_t* pixel_ptr = pixel_data.data();
    for (int j = 0; j < 3;) {
      for (uint32_t i = 0; i < header.height * header.width;
           i++, pixel_ptr += 3, raw_ptr++) {
        if (j == 0) *pixel_ptr |= 0xff000000U;
        *pixel_ptr |= *raw_ptr;
      }
      pixel_ptr = pixel_data.data() + ++j;
    }
  }

 public:
  void read(const std::string& filename) {
    std::ifstream istrm(filename, std::ios::binary);
    if (!istrm) {
      throw std::ios::failure("Cannot open the input file: " + filename);
    }
    istrm.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    if (header.compression_method % 3 != 0 || header.colors_in_palette != 0) {
      // compression_method = 3 also read raw data
      throw std::invalid_argument("Only no compression is supported currently");
    }

    istrm.seekg(header.offset_data, std::ios::beg);
    auto padded_row_size = paddedRowSize();
    bool topDown = false;
    if (header.height < 0) {
      header.height = -header.height;
      topDown = true;
    }
    size_t image_size = header.height * padded_row_size;
    // image_size =image_size>0?image_size:-image_size;
    std::vector<uint8_t> data(image_size);
    pixel_data.reserve(image_size);
    istrm.read(reinterpret_cast<char*>(data.data()), data.size());
    if (topDown) {
      for (int i = 0; i < header.height; i++) {
        auto k = header.height - 1 - i;
        uint32_t c=(header.width * header.bit_per_pixel)/8;
        auto ptr =
            reinterpret_cast<uint8_t*>(data.data()) + k * padded_row_size;
        pixel_data.insert(pixel_data.end(), ptr,
                          ptr + (header.width * header.bit_per_pixel)/8 );
      }
    } else
      pixel_data = data;
  }

  void write(const std::string& filename) {
    // upside down and padding
    int padded_row_size = paddedRowSize();
    // std::vector<uint8_t> image_data(header.image_size);
    int channels = header.bit_per_pixel / 8;
    // for (int i = 0; i < header.height; i++) {
    //   auto k = header.height - 1 - i;
    //   auto ptr = &pixel_data[k * header.width * channels];
    //   std::copy(ptr, ptr + header.width * channels,
    //             &image_data[i * padded_row_size]);
    // }

    std::ofstream ostrm{filename, std::ios_base::binary};
    if (!ostrm) {
      throw std::runtime_error("Cannot open the output file: " + filename);
    }
    ostrm.write((const char*)&header, sizeof header);
    if (is8bit()) {
      constexpr ColorPalette color_palette;
      ostrm.write((const char*)color_palette.table, sizeof(ColorPalette));
    }
    if (header.compression_method == 3) {
      const BitField bit_field;
      ostrm.write((const char*)&bit_field, sizeof(BitField));
    }
    ostrm.write((const char*)pixel_data.data(), pixel_data.size());
  }

  template <typename T>
  void write(const JPEG2000::Matrix3D<T> rawImage,
             const std::string& filename) {
    header.width = rawImage.width();
    header.height = rawImage.height();
    if (rawImage.channel() == 3 && header.compression_method == 3)
      header.bit_per_pixel = (rawImage.channel() + 1) * 8;
    else
      header.bit_per_pixel = rawImage.channel() * 8;
    int padded_row_size = paddedRowSize();
    header.image_size = header.height * padded_row_size;
    header.offset_data = sizeof(header);
    if (header.compression_method == 3) header.offset_data += sizeof(BitField);
    header.file_size = header.offset_data + header.image_size;
    switch (header.bit_per_pixel >> 3) {
      case 3:
        iRGBconvert24(rawImage.addr);
        break;
      case 4:
        iRGBconvert32(rawImage.addr);
        break;

      default:
        break;
    }

    write(filename);
  }

  JPEG2000::Matrix3D<uint8_t> get() {
    std::vector<uint8_t> rgb;
    switch (header.bit_per_pixel >> 3) {
      // case 0:
      // case 1:
      //   // return
      //   //
      //   JPEG2000::Matrix3D<uint8_t>(1,(size_t)header.height,(size_t)header.width,pixel_data);
      // case 2:
      case 3:
        rgb = RGBconvert24();
        break;
      case 4:
        rgb = RGBconvert32(0x00ff0000U, 0x0000ff00U, 0x000000ffU);

        break;

      default:
        throw std::invalid_argument("Bits Per Pixel " +
                                    std::to_string(header.bit_per_pixel) +
                                    " invalid");
        break;
    }
    return JPEG2000::Matrix3D<uint8_t>(3, (size_t)header.height,
                                       (size_t)header.width, rgb);
  }
};

}  // namespace BMP
#endif