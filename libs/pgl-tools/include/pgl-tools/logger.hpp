#pragma once

#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <array>
#include <experimental/source_location>

#include <pgl-tools/ansi.hpp>

using source_location = std::experimental::source_location;

/* TODO: this part can be in the cpp file I think. The tricky part is the friend operator<<
 * TODO: I think we can have something like:
 *       `pgl::info("This is a {} text with {} arguments.") % { "formated", 2 };`
 *       Using tuples and template black magic this can work I think.
 * TODO: be able to display the logs on anything: window on xlib, OpenGL, stdout, file, socket, ...
 */
namespace pgl::tools {

      class logger {
          public:
              enum class level { info, warn, error, debug };

          public:
              logger(const level l, const source_location sl);
              logger();
              static void stream(std::ostream& os);

              logger& format(const char *fmt)
              {
                  *_stream << fmt;
                  return *this;
              }

              logger& format(const char *fmt, auto first, auto... args)
              {
                  auto fmt_view = std::string_view{fmt};
                  auto pos = fmt_view.find_first_of('{');

                  if (fmt[pos+1] == '}') {
                      _stream->write(fmt, pos);
                      *_stream << first;
                      format(fmt + pos + 2, args...);
                  }

                  return *this;
              }

          private:
              static std::ostream* _stream;

              friend std::ostream& operator<<(logger& logger, auto data);
              friend std::ostream& operator<<(logger&& logger, auto data);
      };

      std::ostream& operator<<(logger& logger, auto data)
      {
          *logger._stream << data;
          return *logger._stream;
      }

      std::ostream& operator<<(logger&& logger, auto data)
      {
          *logger._stream << data;
          return *logger._stream;
      }

} /* end of namespace pgl::tools */

namespace pgl {

    tools::logger debug(source_location sl=source_location::current());
    tools::logger info(source_location sl=source_location::current());
    tools::logger warn(source_location sl=source_location::current());
    tools::logger error(source_location sl=source_location::current());
    void entry(source_location sl=source_location::current());

    void logstream(std::ostream& os);

} /* end of namespace pgl */
