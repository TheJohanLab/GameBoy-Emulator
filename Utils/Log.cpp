#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace gbe {

	std::shared_ptr<spdlog::logger> Log::sLogger;

	Log::Log()
	{

	}

	Log::~Log()
	{
	}

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		sLogger = spdlog::stdout_color_mt("GBE");
		sLogger->set_level(spdlog::level::level_enum::trace);
	}

}
