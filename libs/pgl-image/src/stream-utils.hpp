#pragma once

#include <fstream>
#include <vector>

namespace pgl {
  namespace image {
    namespace utils {

      char        get_char  (std::istream& fstream);
      uint8_t     get_uint8 (std::istream& fstream);
      uint16_t    get_uint16(std::istream& fstream);
      uint32_t    get_uint32(std::istream& fstream);
      std::string get_type  (std::istream& fstream);

    } /* end of namespace utils */
  } /* end of namespace image */
} /* end of namespace pgl */
