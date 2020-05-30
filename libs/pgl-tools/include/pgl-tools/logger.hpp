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

		struct LogContext {
			std::string file;
			int line;
			std::string function;
		};

    class BaseLogger {
			public:
				virtual ~BaseLogger();
				void context(
					const LogContext& context
				);
				virtual void write(
					const std::string& msg,
					const LogContext& context
				) = 0;
    };

		constexpr std::array<ansi::color_code, 3> colors = {
			ansi::color_code::bright_white,
			ansi::color_code::bright_yellow,
			ansi::color_code::bright_red
		};
		constexpr std::array<const char*, 3> levels = {
			"[INFO]", "[WARN]", "[ERROR]"
		};
		enum class Level {
			INFO=0, WARN=1, ERROR=2
		};

		template<Level level>
			class Logger : public BaseLogger {
				public:
					virtual void write(
						const std::string& msg,
						const LogContext& context
						) override
					{
						BaseLogger::context(context);
						std::clog
							<< ansi::color(colors[static_cast<int>(level)])
							<< levels[static_cast<int>(level)] << ": "
							<< msg << ansi::clear << '\n';
					}
			};

		template<Level level>
			class LoggerOnce : public Logger<level> {
				private:
					bool logged = false;
				public:
					virtual void write(
						const std::string& msg,
						const LogContext& context)
					{
						if (!logged) {
							Logger<level>::write(msg, context);
							logged = true;
						}
					}
			};

		class LoggerList {
			private:
				using BaseLoggerRef = std::unique_ptr<BaseLogger>;
				std::map<int, BaseLoggerRef> loggers;
				LoggerList() {}

			public:
				template<Level level>
					void log(
						const std::stringstream& ss,
						const LogContext& context,
						bool log_once=false)
					{
						if (!loggers.count(context.line)) {
							if (!log_once)
								loggers[context.line] = std::make_unique<Logger<level>>();
							else
								loggers[context.line] = std::make_unique<LoggerOnce<level>>();
							loggers[context.line]->write(ss.str(), context);
						} else {
							loggers[context.line]->write(ss.str(), context);
						}
					}

				static LoggerList& get() {
					static LoggerList logger_list;
					return logger_list;
				}
		};

  } /* end of namespace tools */
} /* end of namespace pgl */

#define CONCATENATE(x, y) x##y
#define EXPAND(x, y) CONCATENATE(x, y)

#define PGL_INFO_IMP(msg, line, file, func) \
	std::stringstream EXPAND(ss, line);       \
	EXPAND(ss, line) << msg;                  \
	pgl::tools::LoggerList::get().log<pgl::tools::Level::INFO>( \
		EXPAND(ss, line), {file, line, func} \
	)

#define PGL_WARN_IMP(msg, line, file, func) \
	std::stringstream EXPAND(ss, line);       \
	EXPAND(ss, line) << msg;                  \
	pgl::tools::LoggerList::get().log<pgl::tools::Level::WARN>( \
		EXPAND(ss, line), {file, line, func} \
	)

#define PGL_ERROR_IMP(msg, line, file, func) \
	std::stringstream EXPAND(ss, line);        \
	EXPAND(ss, line) << msg;                   \
	pgl::tools::LoggerList::get().log<pgl::tools::Level::ERROR>( \
		EXPAND(ss, line), {file, line, func} \
	)

#define PGL_INFO_ONCE_IMP(msg, line, file, func) \
	std::stringstream EXPAND(ss, line);       \
	EXPAND(ss, line) << msg;                  \
	pgl::tools::LoggerList::get().log<pgl::tools::Level::INFO>( \
		EXPAND(ss, line), {file, line, func}, true \
	)

#define PGL_WARN_ONCE_IMP(msg, line, file, func) \
	std::stringstream EXPAND(ss, line);       \
	EXPAND(ss, line) << msg;                  \
	pgl::tools::LoggerList::get().log<pgl::tools::Level::WARN>( \
		EXPAND(ss, line), {file, line, func}, true \
	)

#define PGL_ERROR_ONCE_IMP(msg, line, file, func) \
	std::stringstream EXPAND(ss, line);       \
	EXPAND(ss, line) << msg;                  \
	pgl::tools::LoggerList::get().log<pgl::tools::Level::ERROR>( \
		EXPAND(ss, line), {file, line, func}, true \
	)

#define PGL_INFO(msg) PGL_INFO_IMP(msg, __LINE__, __FILE__, __FUNCTION__)
#define PGL_WARN(msg) PGL_WARN_IMP(msg, __LINE__, __FILE__, __FUNCTION__)
#define PGL_ERROR(msg) PGL_ERROR_IMP(msg, __LINE__, __FILE__, __FUNCTION__)

#define PGL_INFO_ONCE(msg) PGL_INFO_ONCE_IMP(msg, __LINE__, __FILE__, __FUNCTION__)
#define PGL_WARN_ONCE(msg) PGL_WARN_ONCE_IMP(msg, __LINE__, __FILE__, __FUNCTION__)
#define PGL_ERROR_ONCE(msg) PGL_ERROR_ONCE_IMP(msg, __LINE__, __FILE__, __FUNCTION__)
