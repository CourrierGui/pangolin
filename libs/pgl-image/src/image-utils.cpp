#include "image-utils.hpp"
#include "stream-utils.hpp"

#include <pgl-image/image-loader.hpp>

namespace pgl {

  namespace image {

    constexpr uint8_t PNG_SIGNATURE[8] = {
      0x89, 0x50, 0x4E, 0x47,
      0x0D, 0x0A, 0x1A, 0x0A
    };
    constexpr uint16_t JPEG_SIGNATURE = 0xffd8;

    bool is_png (std::ifstream& fstream) {
      bool res(true);
      for (auto sig: PNG_SIGNATURE) {
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
      Image res;
      return res;
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
