#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include <memory>

namespace Core
{

class Log
{
public:
    static void init();

    inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
    inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }

private:
    static std::shared_ptr<spdlog::logger> s_coreLogger;
    static std::shared_ptr<spdlog::logger> s_clientLogger;
};
}

#define CORE_TRACE(...) SPDLOG_LOGGER_TRACE(Core::Log::getCoreLogger(), __VA_ARGS__)
#define CORE_INFO(...) SPDLOG_LOGGER_INFO(Core::Log::getCoreLogger(), __VA_ARGS__)
#define CORE_WARN(...) SPDLOG_LOGGER_WARN(Core::Log::getCoreLogger(), __VA_ARGS__)
#define CORE_ERROR(...) SPDLOG_LOGGER_ERROR(Core::Log::getCoreLogger(), __VA_ARGS__)
#define CORE_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(Core::Log::getCoreLogger(), __VA_ARGS__)

// Client Log Macros
#define APP_TRACE(...) SPDLOG_LOGGER_TRACE(Core::Log::getClientLogger(), __VA_ARGS__)
#define APP_INFO(...) SPDLOG_LOGGER_INFO(Core::Log::getClientLogger(), __VA_ARGS__)
#define APP_WARN(...) SPDLOG_LOGGER_WARN(Core::Log::getClientLogger(), __VA_ARGS__)
#define APP_ERROR(...) SPDLOG_LOGGER_ERROR(Core::Log::getClientLogger(), __VA_ARGS__)
