#pragma once

#include <utils/logging/Logger.h>

#include <fmt/std.h>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define LOG_MSG(level, message)                                                                                        \
    if (sloth::logging::Logger::Instance().GetLogLevel() <= level) {                                                   \
        std::string file(__FILE__);                                                                                    \
        file = file.erase(0, file.find("/src/") + 5);                                                                  \
        sloth::logging::Logger::Instance().Log(level, message " ({} {}:{}) [{}]", __func__, file, __LINE__,            \
                                               std::this_thread::get_id());                                            \
    }

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define LOG(level, format, ...)                                                                                        \
    if (sloth::logging::Logger::Instance().GetLogLevel() <= level) {                                                   \
        std::string file(__FILE__);                                                                                    \
        file = file.erase(0, file.find("/src/") + 5);                                                                  \
        sloth::logging::Logger::Instance().Log(level, format " ({} {}:{}) [{}]", __VA_ARGS__, __func__, file,          \
                                               __LINE__, std::this_thread::get_id());                                  \
    }

#ifdef STATIC_LOG_LEVEL

#if STATIC_LOG_LEVEL >= STATIC_ERROR_LEVEL
#define LOG_ERROR(...)    LOG(L_ERROR, __VA_ARGS__)     // NOLINT(cppcoreguidelines-macro-usage)
#define LOG_CRITICAL(...) LOG(L_CRITICAL, __VA_ARGS__)  // NOLINT(cppcoreguidelines-macro-usage)
#else
#define LOG_ERROR(...)
#define LOG_CRITICAL(...)
#endif

#if STATIC_LOG_LEVEL >= STATIC_WARN_LEVEL
#define LOG_WARN(...) LOG(L_WARN, __VA_ARGS__)  // NOLINT(cppcoreguidelines-macro-usage)
#else
#define LOG_WARN(...)
#endif

#if STATIC_LOG_LEVEL >= STATIC_INFO_LEVEL
#define LOG_INFO(...) LOG(L_INFO, __VA_ARGS__)  // NOLINT(cppcoreguidelines-macro-usage)
#else
#define LOG_INFO(...)
#endif

#if STATIC_LOG_LEVEL >= STATIC_DEBUG_LEVEL
#define LOG_DEBUG(...) LOG(L_DEBUG, __VA_ARGS__)  // NOLINT(cppcoreguidelines-macro-usage)
#else
#define LOG_DEBUG(...)
#endif

#if STATIC_LOG_LEVEL >= STATIC_TRACE_LEVEL
#define LOG_TRACE(...) LOG(L_TRACE, __VA_ARGS__)  // NOLINT(cppcoreguidelines-macro-usage)
#else
#define LOG_TRACE(...)
#endif

#else
#define LOG_TRACE(...)     // NOLINT(cppcoreguidelines-macro-usage)
#define LOG_DEBUG(...)     // NOLINT(cppcoreguidelines-macro-usage)
#define LOG_INFO(...)      // NOLINT(cppcoreguidelines-macro-usage)
#define LOG_WARN(...)      // NOLINT(cppcoreguidelines-macro-usage)
#define LOG_ERROR(...)     // NOLINT(cppcoreguidelines-macro-usage)
#define LOG_CRITICAL(...)  // NOLINT(cppcoreguidelines-macro-usage)
#endif
