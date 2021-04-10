#include <pgl-tools/logger.hpp>

#include <filesystem>
#include <chrono>
#include <ctime>
#include <unordered_set>
#include <fstream>

const auto start_time = std::chrono::system_clock::now();
using namespace std::chrono_literals;
std::unordered_set<std::string> loggers;
std::ofstream dev_null{"/dev/null"};

namespace pgl {
  namespace tools {

    auto log(const LogContext& context) -> std::ostream& {
      if (context.log_once
          && loggers.contains(context.file+std::to_string(context.line))) {
        loggers.insert(context.file+std::to_string(context.line));
        return dev_null;
      }

      std::filesystem::path p{context.file};
      auto now = std::chrono::system_clock::now();

      if (context.level != Level::NONE)
        std::cerr << ansi::color(colors[static_cast<int>(context.level)]);

      std::cerr
        << '[' << std::fixed << std::setw(9)
        << ((now-start_time) / 1us) / 1'000'000.0 << "] "
        << p.filename() << ':'
        << context.line << ':'
        << context.function << ':';

      if (context.level != Level::NONE) {
        std::cerr
          << ' ' << levels[static_cast<int>(context.level)]
          << ansi::clear;
      }

      std::cerr << ' ';
      loggers.insert(context.file+std::to_string(context.line));
      return std::cerr;
    }

  } /* end of namespace tools */
} /* end of namespace pgl */
