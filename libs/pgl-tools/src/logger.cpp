#include <pgl-tools/logger.hpp>
#include <pgl-tools/ansi.hpp>

#include <iostream>

namespace pgl {
	namespace tools {

		Logger::~Logger() {}

		InfoLogger::InfoLogger() {}
		void InfoLogger::write(
			const std::string& msg,
			const LogContext& context)
		{
			std::clog
				<< "In file "
				<< ansi::color(ansi::color_code::bright_blue)
				<< context.file << ": "
				<< ansi::color(ansi::color_code::bright_green)
				<< "Line "
				<< context.line << ' '
				<< ansi::escape
				<< "in function "
				<< ansi::color(ansi::color_code::bright_yellow)
				<< context.function << ":\n"
				<< ansi::color(ansi::color_code::bright_white)
				<< "[INFO]: "
				<< msg
				<< ansi::escape << '\n';
		}

		WarnLogger::WarnLogger() {}
		void WarnLogger::write(
			const std::string& msg,
			const LogContext& context)
		{
			std::clog
				<< "In file "
				<< ansi::color(ansi::color_code::bright_blue)
				<< context.file << ": "
				<< ansi::color(ansi::color_code::bright_green)
				<< "Line "
				<< context.line << ' '
				<< ansi::escape
				<< "in function "
				<< ansi::color(ansi::color_code::bright_yellow)
				<< context.function << ":\n"
				<< ansi::color(ansi::color_code::bright_magenta)
				<< "[WARN]: " << msg
				<< ansi::escape << '\n';
		}

		ErrorLogger::ErrorLogger() {}
		void ErrorLogger::write(
			const std::string& msg,
			const LogContext& context)
		{
			std::clog
				<< "In file "
				<< ansi::color(ansi::color_code::bright_blue)
				<< context.file << ": "
				<< ansi::color(ansi::color_code::bright_green)
				<< "Line "
				<< context.line << ' '
				<< ansi::escape
				<< "in function "
				<< ansi::color(ansi::color_code::bright_yellow)
				<< context.function << ":\n"
				<< ansi::color(ansi::color_code::bright_red)
				<< "[ERROR]: " << msg
				<< ansi::escape << '\n';
		}

		void log_info(
			const std::stringstream& ss,
			const LogContext& context)
		{
			static InfoLogger info_logger;
			return info_logger.write(ss.str(), context);
		}

		void log_warn(
			const std::stringstream& ss,
			const LogContext& context)
		{
			static WarnLogger warn_logger;
			warn_logger.write(ss.str(), context);
		}

		void log_error(
			const std::stringstream& ss,
			const LogContext& context)
		{
			static ErrorLogger error_logger;
			error_logger.write(ss.str(), context);
		}

	} /* end of namespace tools */
} /* end of namespace pgl */
