#include <utils/logging/log.h>

namespace {

constexpr const char* LOGGER_NAME = "logger";

// Message example
// [2022-08-16 09:49:56.299] [ INFO] Diagnostic message
constexpr const char* LOG_PATTERN = "[%Y-%m-%d %H:%M:%S.%e] [%^%5l%$] %v";

spdlog::sink_ptr CreateStderrSink(sloth::logging::LoggingSettings::SyncMode syncMode, LOG_LEVEL level)
{
    spdlog::sink_ptr sink;
    if (syncMode == sloth::logging::LoggingSettings::SyncMode::Sync) {
        sink = std::make_shared<spdlog::sinks::stderr_color_sink_st>();
    } else {
        sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
    }
    sink->set_level(level);

    return sink;
}

}  // namespace

namespace sloth::logging {

Logger::Logger()
{
    SetSettings(LoggingSettings());

    // Set default logger to stderr
    // It will be used in LogToDefault
    auto defaultLogger = spdlog::stderr_color_mt("default_logger");
    defaultLogger->set_pattern(LOG_PATTERN, spdlog::pattern_time_type::utc);
    spdlog::set_default_logger(defaultLogger);
}

Logger& Logger::Instance()
{
    static Logger obj;
    return obj;
}

void Logger::SetSettings(LoggingSettings&& settings)
{
    Reset();

    // Create stderr sink with level L_TRACE to grab all messages in backtrace
    _logger = std::make_shared<spdlog::logger>(LOGGER_NAME, CreateStderrSink(settings.GetSyncMode(), L_TRACE));
    if (settings.GetBacktraceSize() != 0) {
        _logger->enable_backtrace(settings.GetBacktraceSize());
    }

    _logger->set_pattern(LOG_PATTERN, spdlog::pattern_time_type::utc);
}

void Logger::Reset()
{
    if (!_logger) {
        return;
    }

    spdlog::shutdown();
    _logger.reset();
}

void Logger::SetLogLevel(LOG_LEVEL level)
{
    if (_logger) {
        _logger->set_level(level);
    }
}

LOG_LEVEL Logger::GetLogLevel() const { return _logger ? _logger->level() : L_OFF; }

void Logger::DumpBacktrace()
{
    if (_logger) {
        _logger->dump_backtrace();
    }
}

}  // namespace sloth::logging