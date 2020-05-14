#pragma once

#include <string>

namespace pgl {
  namespace loader {

struct Image;

Image load_png(const std::string& filename);

struct Image {
  unsigned int width, height, depth;
  const char* data;
};

  } /* end of namespace loader */
} /* end of namespace pgl */
