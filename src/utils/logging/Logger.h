#pragma once

#include <utils/logging/LoggingSettings.h>

#include <thread>
#include <string_view>

namespace sloth::logging {

class Logger final
{
public:
    static Logger& Instance();

    Logger(const Logger&) = delete;
    Logger(Logger&&)      = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

    void SetSettings(LoggingSettings&& settings);
    void Reset();
    void SetLogLevel(LOG_LEVEL);
    LOG_LEVEL GetLogLevel() const;
    void DumpBacktrace();

    template <typename FormatString, typename... Args>
    void Log(LOG_LEVEL level, const FormatString& str, Args&&... args)
    {
        if (_logger) {
            _logger->log(level, str, std::forward<Args>(args)...);
        }
    }

    template <typename FormatString, typename... Args>
    void LogToDefault(LOG_LEVEL level, const FormatString& str, Args&&... args)
    {
        spdlog::log(level, str, std::forward<Args>(args)...);
    }

private:
    Logger();
    ~Logger() = default;

    std::shared_ptr<spdlog::logger> _logger;
};

}  // namespace sloth::logging
