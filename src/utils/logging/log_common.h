#pragma once

#include <string_view>
// Undefine GLOG macro
#ifdef LOG
#undef LOG
#endif

#ifdef LOG_TRACE
#undef LOG_TRACE
#endif
#ifdef LOG_DEBUG
#undef LOG_DEBUG
#endif
#ifdef LOG_INFO
#undef LOG_INFO
#endif
#ifdef LOG_ERROR
#undef LOG_ERROR
#endif
#ifdef LOG_WARN
#undef LOG_WARN
#endif

namespace detail {

using namespace std::literals::string_view_literals;
constexpr auto kTRACE    = "TRACE"sv;
constexpr auto kDEBUG    = "DEBUG"sv;
constexpr auto kINFO     = "INFO"sv;
constexpr auto kWARNING  = "WARNING"sv;
constexpr auto kERROR    = "ERROR"sv;
constexpr auto kCRITICAL = "CRITICAL"sv;
constexpr auto kOFF      = "OFF"sv;
}  // namespace detail

//NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
//NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define SPDLOG_LEVEL_NAMES                                                                                             \
    {                                                                                                                  \
        detail::kTRACE, detail::kDEBUG, detail::kINFO, detail::kWARNING, detail::kERROR, detail::kCRITICAL,            \
            detail::kOFF                                                                                               \
    }

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using LOG_LEVEL                = spdlog::level::level_enum;
constexpr LOG_LEVEL L_TRACE    = spdlog::level::trace;
constexpr LOG_LEVEL L_DEBUG    = spdlog::level::debug;
constexpr LOG_LEVEL L_INFO     = spdlog::level::info;
constexpr LOG_LEVEL L_WARN     = spdlog::level::warn;
constexpr LOG_LEVEL L_ERROR    = spdlog::level::err;
constexpr LOG_LEVEL L_CRITICAL = spdlog::level::critical;
constexpr LOG_LEVEL L_OFF      = spdlog::level::off;
