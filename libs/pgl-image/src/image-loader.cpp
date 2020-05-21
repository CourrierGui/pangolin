#include <pgl-image/image-loader.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

#include "image-utils.hpp"
#include "../tests/stb_image/stb_image.h"

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

      /* return extract_image(fstream); */
      Image res;
      int width, height, nb_channels;
      unsigned char* data
        = stbi_load(filename.c_str(), &width, &height, &nb_channels, 0);
      res.width  = width;
      res.height = height;
      res.depth  = nb_channels;
      res.data   = std::vector<unsigned char>(data, data+width*height*nb_channels);
      return res;
    }

  } /* end of namespace image */
} /* end of namespace pgl */
