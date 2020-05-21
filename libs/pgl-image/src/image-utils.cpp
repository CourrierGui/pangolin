#include "image-utils.hpp"
#include "stream-utils.hpp"
#include "png.hpp"

#include <pgl-image/image-loader.hpp>

#include <iostream>

namespace pgl {

  namespace image {

    constexpr uint16_t JPEG_SIGNATURE = 0xffd8;

    bool is_png (std::ifstream& fstream) {
      bool res(true);
      for (auto sig: png::SIGNATURE) {
        res &= (sig == utils::get_uint8(fstream));
      }
      return res;
    }

    bool is_jpeg(std::ifstream& fstream) {
      uint16_t signature = utils::get_uint16(fstream);
      return signature == JPEG_SIGNATURE;
    }

    bool is_gif (std::ifstream& fstream) {

    }

    Image extract_png (std::ifstream& fstream) {
      Image image;

      png::IHDR ihdr = png::extract_ihdr(fstream);
      image.width  = ihdr.width;
      image.height = ihdr.height;
      std::clog << "Compression: " << (int)ihdr.compression_method
        << " Filter: " << (int)ihdr.filter_method
        << " Interlace: " << (int)ihdr.interlace_method << '\n';

      uint8_t pixel_size = 0;
      switch (ihdr.color_type) {
        case 0:
          image.depth = 1;
          pixel_size = 1; //grayscale
          break;
        case 2:
          image.depth = 3;
          pixel_size = 3; //RGB
          break;
        case 3:
          //see PLTE chunk
          throw std::runtime_error("PTLE chunk not supported yet. :'(");
          break;
        case 4:
          image.depth = 2;
          pixel_size = 2;
          break;
        case 6:
          image.depth = 4;
          pixel_size = 4;
          break;
      }

      if (ihdr.bit_depth == 16)
        pixel_size *= 2;

      std::string type;
      type.reserve(4);
      uint32_t size;

      while (true) {
        size = utils::get_uint32(fstream);
        type = utils::get_type(fstream);
        std::clog << "type: " << type << '\n';
        if (!png::valid_type(type)) {
          std::clog << "size: " << size << ", type: " << type << '\n';
          png::next_chunk(fstream, size, type);
        }

        if (type == "IDAT") {
          auto it = std::back_insert_iterator(image.data);
          png::read_idat(fstream, size, ihdr, it);
          png::check_control(fstream);
        } else if (type == "IEND") {
          break;
        } else {
          png::skip_chunk(fstream, size);
        }
      }
      return image;
    }

    Image extract_jpeg(std::ifstream& fstream) {
      Image res;
      return res;
    }

    Image extract_gif (std::ifstream& fstream) {
      Image res;
      return res;
    }

  } /* end of namespace image */
} /* end of namespace pgl */
