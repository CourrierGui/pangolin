#include <pgl-tools/logger.hpp>

#include <iostream>

namespace pgl {
	namespace tools {

		BaseLogger::~BaseLogger() {}
		void BaseLogger::context(
			const LogContext& context)
		{
			std::clog
				<< "In file "
				<< ansi::color(ansi::color_code::bright_blue)
				<< context.file << ": "
				<< ansi::color(ansi::color_code::bright_green)
				<< "line "
				<< context.line << ' '
				<< ansi::clear
				<< "in function "
				<< ansi::color(ansi::color_code::bright_yellow)
				<< context.function << ":\n";
		}

		LoggerList::LoggerList() = default;

		LoggerList& LoggerList::get() {
			static LoggerList logger_list;
			return logger_list;
		}

	} /* end of namespace tools */
} /* end of namespace pgl */
