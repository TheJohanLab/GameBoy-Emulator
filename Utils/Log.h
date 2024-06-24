#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace gbe {

	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> sLogger;

	public:
		Log();
		~Log();

		static void init();

		inline static std::shared_ptr<spdlog::logger>& getLogger() { return sLogger; }

	};

}



//log macros
#define GBE_LOG_TRACE(...) ::gbe::Log::getLogger()->trace(__VA_ARGS__)
#define GBE_LOG_INFO(...)  ::gbe::Log::getLogger()->info(__VA_ARGS__)
#define GBE_LOG_WARN(...)  ::gbe::Log::getLogger()->warn(__VA_ARGS__)
#define GBE_LOG_ERROR(...) ::gbe::Log::getLogger()->error(__VA_ARGS__)
