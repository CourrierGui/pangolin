#pragma once

#include <fstream>
#include <array>
#include <vector>
#include <string>

namespace pgl {
  namespace image {
    namespace png {

      constexpr uint8_t SIGNATURE[8] = {
        0x89, 0x50, 0x4E, 0x47,
        0x0D, 0x0A, 0x1A, 0x0A
      };

      const std::array<std::string, 18> TYPES = {
        "IDAT", "PLTE", "cHRM", "gAMA", "iCCP",
        "sBIT", "sRGB", "bKGD", "hIST", "tRNS",
        "pHYs", "sPLT", "tIME", "iTXt", "tEXt",
        "zTXt", "IEND", "IHDR"
      };

      struct IHDR {
        uint32_t width, height;
        uint8_t bit_depth, color_type;
        uint8_t compression_method;
        uint8_t filter_method, interlace_method;
      };

      using pixel_it = std::back_insert_iterator<std::vector<unsigned char>>;

      IHDR extract_ihdr(std::istream& fstream);

      void extract_pixels(std::istream& fstream, const IHDR& ihdr, pixel_it& it);

      void read_idat(
        std::istream& fstream, const uint32_t size,
        const IHDR& ihdr, pixel_it& it
      );

      bool valid_type(const std::string& type);

      void next_chunk(
        std::istream& fstream, uint32_t& size, std::string& type
      );

      void skip_chunk(std::istream& fstream, const uint32_t size);

      bool check_control(std::istream& fstream);

    } /* end of namespace png */
  } /* end of namespace png */
} /* end of namespace png */
