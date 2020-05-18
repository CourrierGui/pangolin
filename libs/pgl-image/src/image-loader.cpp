#include <pgl-image/image-loader.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

#include "image-utils.hpp"

namespace pgl {
  namespace image {

    Image extract_image(std::ifstream& fstream) {
      if      (is_png(fstream) ) return extract_png (fstream);
      else if (is_jpeg(fstream)) return extract_jpeg(fstream);
      else if (is_gif(fstream) ) return extract_gif (fstream);
      else throw std::runtime_error("Unsupported file type.");
    }

    Image load_image(const std::string& filename) {
      std::ifstream fstream(filename, std::ios::binary);

      if (!fstream.is_open())
        throw std::runtime_error("File not found: " + filename);

      return extract_image(fstream);
    }

  } /* end of namespace image */
} /* end of namespace pgl */
