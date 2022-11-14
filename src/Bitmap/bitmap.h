#ifndef BITMAP_H
#define BITMAP_H
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
  uint32_t compression_method{0};  // compression method: 0 - uncompressed.
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
  int paddedRowSize() const {
    return ((header.width * header.bit_per_pixel + 31) / 32) * 4;
  }
  std::vector<uint8_t> pixel_data;

 public:
  void read(const std::string& filename) {
    std::ifstream istrm(filename, std::ios::binary);
    if (!istrm) {
      throw std::ios::failure("Cannot open the input file: " + filename);
    }
    istrm.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    if (header.compression_method != 0 || header.colors_in_palette != 0) {
      throw std::invalid_argument("Only no compression is supported currently");
    }

    istrm.seekg(header.offset_data, std::ios::beg);
    int padded_row_size = paddedRowSize();
    int image_size = header.height * padded_row_size;
    std::vector<uint8_t> data(image_size);
    istrm.read(reinterpret_cast<char*>(data.data()), data.size());

    pixel_data.reserve((header.width * header.height * header.bit_per_pixel) /
                       8);
    for (int i = 0; i < header.height; i++) {
      auto k = header.height - 1 - i;
      auto ptr = reinterpret_cast<uint8_t*>(data.data()) + k * padded_row_size;
      pixel_data.insert(pixel_data.end(), ptr,
                        ptr + (header.width * header.bit_per_pixel) / 8);
    }
  }
  void write(const std::string& filename) {
    // upside down and padding
    int padded_row_size = paddedRowSize();
    std::vector<uint8_t> image_data(header.image_size);
    int channels = header.bit_per_pixel / 8;
    for (int i = 0; i < header.height; i++) {
      auto k = header.height - 1 - i;
      auto ptr = &pixel_data[k * header.width * channels];
      std::copy(ptr, ptr + header.width * channels,
                &image_data[i * padded_row_size]);
    }

    std::ofstream ostrm{filename, std::ios_base::binary};
    if (!ostrm) {
      throw std::runtime_error("Cannot open the output file: " + filename);
    }
    ostrm.write((const char*)&header, sizeof header);
    if (is8bit()) {
      constexpr ColorPalette color_palette;
      ostrm.write((const char*)color_palette.table, sizeof(ColorPalette));
    }
    ostrm.write((const char*)image_data.data(), image_data.size());
  }
  template<typename T>
  void write(const Matrix<T> rawImage, const std::string& filename) {
    header.width = rawImage.width();
    header.height = rawImage.height();
    header.bit_per_pixel = rawImage.channels * 8;
    int padded_row_size = paddedRowSize();
    header.image_size = header.height * padded_row_size;
    header.offset_data = sizeof(header) + sizeof(ColorPalette);
    header.file_size = header.offset_data + header.image_size;
    pixel_data.resize(rawImage.width() * rawImage.height() * rawImage.channels);
    std::copy(rawImage.data, rawImage.data + pixel_data.size(),
              pixel_data.begin());
    write(filename);
  }

  ImageView get() {
    return {header.width, header.height, header.bit_per_pixel / 8,
            pixel_data.data()};
  }
}

}  // namespace BMP
#endif