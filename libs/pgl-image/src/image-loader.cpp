#include <pgl-image/image-loader.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

#include "crc.hpp"
#include "png.hpp"

namespace pgl {
  namespace loader {

Image load_png(const std::string& filename) {
  std::ifstream fstream(filename, std::ios::binary);

  if (!fstream.is_open()) {
    throw std::runtime_error("File not found: " + filename);

  }

  PNG png(fstream);
  return Image();
}

  } /* end of namespace loader */
} /* end of namespace pgl */
