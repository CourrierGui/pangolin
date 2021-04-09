#pragma once

#include <string>
#include <vector>

namespace pgl {

  struct Image {
    Image();
    uint32_t width, height;
    uint8_t depth;
    std::vector<unsigned char> data;
  };

  namespace image {

    //TODO static method of struct Image?
    auto load_image(const std::string& filename) -> Image;

  } /* end of namespace image */
} /* end of namespace pgl */
