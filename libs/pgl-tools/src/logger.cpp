#include <pgl-tools/logger.hpp>

#include <filesystem>
#include <chrono>
#include <ctime>
#include <unordered_set>
#include <fstream>
#include <filesystem>

namespace pgl {
    namespace tools {

        constexpr std::array<ansi::color_code, 3> colors[[maybe_unused]] = {
            ansi::color_code::bright_white,
            ansi::color_code::bright_yellow,
            ansi::color_code::bright_red
        };

        constexpr std::array<const char*, 4> levels = {
            "<INFO> ", "<WARN> ", "<ERROR>", "<DEBUG>"
        };

        std::ostream* logger::_stream = &std::clog;
        level logger::_global_level = level::info;

        logger::logger(const level l, const source_location sl) :
            _level{l}
        {
            if (!should_display())
                return;

            std::filesystem::path p{sl.file_name()};
            *_stream
                << levels[static_cast<int>(l)] << ' '
                << p.filename().c_str() << ':'
                << sl.line() << ": "
                << sl.function_name() << "(): ";
        }

        void logger::stream(std::ostream& os)
        {
            _stream = &os;
        }

        void logger::loglevel(level l)
        {
            _global_level = l;
        }

    } /* end of namespace tools */

    tools::logger debug(source_location sl)
    {
        return tools::logger{level::debug, sl};
    }

    tools::logger info(source_location sl)
    {
        return tools::logger{level::info, sl};
    }

    tools::logger warn(source_location sl)
    {
        return tools::logger{level::warn, sl};
    }

    tools::logger error(source_location sl)
    {
        return tools::logger{level::error, sl};
    }

    void logstream(std::ostream& os)
    {
        tools::logger::stream(os);
    }

    void entry(source_location sl)
    {
        tools::logger().format(
            "entering {} at {} in {}\n",
            sl.function_name(), sl.line(), sl.file_name());
    }

    void loglevel(pgl::level level)
    {
        tools::logger::loglevel(level);
    }

} /* end of namespace pgl */
