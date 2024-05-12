#pragma once


#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"//�������Զ���������Զ���ostream<< ���������



namespace Hazel{
	class HAZEL_API Log
	{
	public:
		static void Init();

		inline static Hazel::Ref<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
		inline static Hazel::Ref<spdlog::logger> GetClientLogger() { return s_ClientLogger; }

	private:
		static Hazel::Ref<spdlog::logger> s_CoreLogger;
		static Hazel::Ref<spdlog::logger> s_ClientLogger;

	};


}

//core loggers macros
#define HZ_CORE_TRACE(...)  ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)   ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)   ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)  ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_FATAL(...)  ::Hazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client loggers macros
#define HZ_TRACE(...)  ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)   ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)   ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)  ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_FATAL(...)  ::Hazel::Log::GetClientLogger()->fatal(__VA_ARGS__)
