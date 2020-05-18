#include "stream-utils.hpp"

namespace pgl {
  namespace image {
    namespace utils {

      char get_char(std::istream& fstream) {
        char c;
        fstream.get(c);
        return c;
      }

      uint8_t get_uint8(std::istream& fstream) {
        char c;
        fstream.get(c);
        return (uint8_t)c;
      }

      uint16_t get_uint16(std::istream& fstream) {
        char c;
        uint16_t res = 0;
        fstream.get(c); res += ((unsigned char)c << 8);
        fstream.get(c); res +=  (unsigned char)c;
        return res;
      }

      uint32_t get_uint32(std::istream& fstream) {
        char c;
        uint32_t res = 0;

        fstream.get(c); res += ((unsigned char)c << 24);
        fstream.get(c); res += ((unsigned char)c << 16);
        fstream.get(c); res += ((unsigned char)c <<  8);
        fstream.get(c); res +=  (unsigned char)c;

        return res;
      }

      //TODO: move to png.hpp
      std::string get_type(std::istream& fstream) {
        std::string res;
        char c;
        for (int i=0; i<4; ++i) {
          fstream.get(c);
          res.push_back(c);
        }
        return res;
      }

    } /* end of namespace utils */

  } /* end of namespace image */

} /* end of namespace pgl */
