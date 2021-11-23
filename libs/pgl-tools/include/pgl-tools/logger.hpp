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

/* The goal is to be able to display these logs on anything: XWindow, wayland,
 * OpenGL context, ...
 * These will have to implement some kind of stream to display messages.
 * For example:
 *
 * pgl::gui::debug logger;
 *
 * logger << "This is a debug message\n";
 *
 *
 * TODO The logs could look like something like this:
 *
 * pgl::info("This is a {} text with {} arguments.") % { "formated", 2 };
 */
namespace pgl {
    enum class level { debug, info, warn, error };

    namespace tools {

        class logger {
            public:

                logger(const level l, const source_location sl);
                logger() = default;

                static void stream(std::ostream& os);
                static void loglevel(level l);

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

                inline bool should_display()
                {
                    return _level >= _global_level;
                }

            private:
                static std::ostream* _stream;
                static level _global_level;
                level _level = level::info;

                friend std::ostream& operator<<(logger& logger, auto data);
                friend std::ostream& operator<<(logger&& logger, auto data);
        };

        std::ostream& operator<<(logger& logger, auto data)
        {
            if (!logger.should_display())
                return *logger._stream;

            *logger._stream << data;
            return *logger._stream;
        }

        std::ostream& operator<<(logger&& logger, auto data)
        {
            if (!logger.should_display())
                return *logger._stream;

            *logger._stream << data;
            return *logger._stream;
        }

    } /* end of namespace tools */

    tools::logger debug(source_location sl=source_location::current());
    tools::logger info(source_location sl=source_location::current());
    tools::logger warn(source_location sl=source_location::current());
    tools::logger error(source_location sl=source_location::current());
    void entry(source_location sl=source_location::current());

    void logstream(std::ostream& os);
    void loglevel(level level);

} /* end of namespace pgl */
