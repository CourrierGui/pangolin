#include <pgl-tools/logger.hpp>

#include <filesystem>
#include <chrono>
#include <ctime>
#include <unordered_set>
#include <fstream>

namespace pgl::tools {

    constexpr std::array<ansi::color_code, 3> colors[[maybe_unused]] = {
      ansi::color_code::bright_white,
      ansi::color_code::bright_yellow,
      ansi::color_code::bright_red
    };

    constexpr std::array<const char*, 4> levels[[maybe_unused]] = {
      "<INFO> ", "<WARN> ", "<ERROR>", "<ENTRY>",
    };

    logger::logger(const level l, const source_location sl) :
        _level{l}, _source{sl}
    {
    }

    std::ostream* logger::_stream = &std::clog;

    void logger::stream(std::ostream& os)
    {
        _stream = &os;
    }

} /* end of namespace pgl::tools */

namespace pgl {

    tools::logger debug(source_location sl)
    {
        return tools::logger{tools::logger::level::debug, sl};
    }

    tools::logger info(source_location sl)
    {
        return tools::logger{tools::logger::level::info, sl};
    }

    tools::logger warn(source_location sl)
    {
        return tools::logger{tools::logger::level::warn, sl};
    }

    tools::logger error(source_location sl)
    {
        return tools::logger{tools::logger::level::error, sl};
    }

    void logstream(std::ostream& os)
    {
        tools::logger::stream(os);
    }

    void entry(source_location sl)
    {
        info(sl).format("entering {} at {} in {}\n",
                        sl.function_name(), sl.line(), sl.file_name());
    }

} /* end of namespace pgl */
