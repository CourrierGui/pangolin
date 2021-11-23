#include <iostream>
#include <string>
#include <chrono>
#include <sstream>

namespace pgl::tools::ansi {

      enum class color_code: int {
        black   = 30, bg_black   = 40,
        red     = 31, bg_red     = 41,
        green   = 32, bg_green   = 42,
        yellow  = 33, bg_yellow  = 43,
        blue    = 34, bg_blue    = 44,
        magenta = 35, bg_magenta = 45,
        cyan    = 36, bg_cyan    = 46,
        white   = 37, bg_white   = 47,

        bright_black   = 90, bg_bright_black   = 100,
        bright_red     = 91, bg_bright_red     = 101,
        bright_green   = 92, bg_bright_green   = 102,
        bright_yellow  = 93, bg_bright_yellow  = 103,
        bright_blue    = 94, bg_bright_blue    = 104,
        bright_magenta = 95, bg_bright_magenta = 105,
        bright_cyan    = 96, bg_bright_cyan    = 106,
        bright_white   = 97, bg_bright_white   = 107,
      };

      constexpr const char clear[7] = "\033[0m";
      constexpr const char escape[5] = "\033[";

      inline std::string color(color_code color) {
        std::stringstream sstr;
        sstr << "\033[1;" << static_cast<int>(color) << "m";
        return sstr.str();
      }

      inline std::string fg_color(int n) {
        std::stringstream sstr;
        sstr
          << escape
          << "38;5;"
          << n
          << "m";
        return sstr.str();
      }

      inline std::string bg_color(int n) {
        std::stringstream sstr;
        sstr
          << escape
          << "48;5;"
          << n
          << "m";
        return sstr.str();
      }

      inline std::string fg_color(int r, int g, int b) {
        std::stringstream sstr;
        sstr
          << escape
          << "38;5;"
          << r << ';'
          << g << ';'
          << b << 'm';
        return sstr.str();
      }

      inline std::string bg_color(int r, int g, int b) {
        std::stringstream sstr;
        sstr
          << escape
          << "48;5;"
          << r << ';'
          << g << ';'
          << b << 'm';
        return sstr.str();
      }

      inline std::string cursor_up(int n) {
        std::stringstream sstr;
        sstr
          << escape
          << n
          << 'A';
        return sstr.str();
      }

      template<typename printable>
        inline std::string print_as_color(printable const& value, color_code color) {
          std::stringstream sstr;
          sstr
            << "\033[1;"
            << static_cast<int>(color)
            << "m" << value << "\033[0m";
          return sstr.str();
        }

      template<color_code color, typename printable>
        inline std::string print_as_color(printable const& value) {
          std::stringstream sstr;
          sstr
            << "\033[1;"
            << static_cast<int>(color)
            <<"m" << value << "\033[0m";
          return sstr.str();
        }

} /* end of namespace pgl::tools::ansi */
