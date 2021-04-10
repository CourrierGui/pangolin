#pragma once

#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <array>

#include <pgl-tools/ansi.hpp>

namespace pgl {
  namespace tools {

    constexpr std::array<ansi::color_code, 3> colors = {
      ansi::color_code::bright_white,
      ansi::color_code::bright_yellow,
      ansi::color_code::bright_red
    };

    constexpr std::array<const char*, 3> levels = {
      "<INFO> ", "<WARN> ", "<ERROR>"
    };

    enum class Level {
      INFO=0, WARN, ERROR, NONE
    };

    struct LogContext {
      std::string file;
      int line;
      std::string function;
      Level level;
      bool log_once;
    };

    auto log(const LogContext& context) -> std::ostream&;

  } /* end of namespace tools */
} /* end of namespace pgl */

#define GENERIC_LOG(level) \
  pgl::tools::log({__FILE__, __LINE__, __FUNCTION__, (pgl::tools::Level::level), false})

#define GENERIC_LOG_ONCE(level) \
  pgl::tools::log({__FILE__, __LINE__, __FUNCTION__, (pgl::tools::Level::level), true})

#define PglInfo  GENERIC_LOG(INFO)
#define PglWarn  GENERIC_LOG(WARN)
#define PglError GENERIC_LOG(ERROR)

#define PglInfoOnce  GENERIC_LOG_ONCE(INFO)
#define PglWarnOnce  GENERIC_LOG_ONCE(WARN)
#define PglErrorOnce GENERIC_LOG_ONCE(ERROR)
