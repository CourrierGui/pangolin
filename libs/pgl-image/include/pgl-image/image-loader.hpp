#pragma once

#include <string>
#include <vector>

namespace pgl {

  struct Image {
    uint32_t width, height;
    uint8_t depth;
    std::vector<char> data;
  };

  namespace image {

    Image load_image(const std::string& filename);

  } /* end of namespace image */
} /* end of namespace pgl */
