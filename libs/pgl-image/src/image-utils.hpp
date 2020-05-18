#pragma once

#include <fstream>

namespace pgl {
  class Image;

  namespace image {

    bool is_png (std::ifstream& fstream);
    bool is_jpeg(std::ifstream& fstream);
    bool is_gif (std::ifstream& fstream);

    Image extract_png (std::ifstream& fstream);
    Image extract_jpeg(std::ifstream& fstream);
    Image extract_gif (std::ifstream& fstream);

  } /* end of namespace image */
} /* end of namespace pgl */
