#pragma once

#include <string>
#include <sstream>
#include <iostream>

namespace pgl {
  namespace tools {

		struct LogContext {
			std::string file;
			int line;
			std::string function;
		};

    class Logger {
			public:
				virtual ~Logger();
				virtual void write(
					const std::string& msg,
					const LogContext& context
				) = 0;
    };

		class InfoLogger : public Logger {
			public:
				void write(
					const std::string& msg,
					const LogContext& context
				) override;

			private:
				InfoLogger();

				friend void log_info(
					const std::stringstream& ss,
					const LogContext& context
				);
		};

		class WarnLogger : public Logger {
			public:
				void write(
					const std::string& msg,
					const LogContext& context
				) override;

			private:
				WarnLogger();
				friend void log_warn(
					const std::stringstream& ss,
					const LogContext& context
				);
		};

		class ErrorLogger : public Logger {
			public:
				void write(
					const std::string& msg,
					const LogContext& context
				) override;

			private:
				ErrorLogger();
				friend void log_error(
					const std::stringstream& ss,
					const LogContext& context
				);
		};

		void log_info (
			const std::stringstream& ss,
			const LogContext& context
		);
		void log_warn(
			const std::stringstream& ss,
			const LogContext& context
		);
		void log_error(
			const std::stringstream& ss,
			const LogContext& context
		);

  } /* end of namespace tools */
} /* end of namespace pgl */

#define CONCATENATE(x, y) x##y
#define EXPAND(x, y) CONCATENATE(x, y)

#define PGL_INFO_IMP(msg, line, file, func) \
	std::stringstream EXPAND(ss, line);       \
	EXPAND(ss, line) << msg;                  \
	pgl::tools::log_info(EXPAND(ss, line), {file, line, func})

#define PGL_WARN_IMP(msg, line, file, func) \
	std::stringstream EXPAND(ss, line);       \
	EXPAND(ss, line) << msg;                  \
	pgl::tools::log_warn(EXPAND(ss, line), {file, line, func})

#define PGL_ERROR_IMP(msg, line, file, func) \
	std::stringstream EXPAND(ss, line);        \
	EXPAND(ss, line) << msg;                   \
	pgl::tools::log_error(EXPAND(ss, line), {file, line, func})

#define PGL_INFO(msg) PGL_INFO_IMP(msg, __LINE__, __FILE__, __FUNCTION__)
#define PGL_WARN(msg) PGL_WARN_IMP(msg, __LINE__, __FILE__, __FUNCTION__)
#define PGL_ERROR(msg) PGL_ERROR_IMP(msg, __LINE__, __FILE__, __FUNCTION__)
