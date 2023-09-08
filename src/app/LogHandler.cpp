#include <QString>

#include <fmt/color.h>

#include <utils/logging/log.h>
#include <utils/logging/format/Qt.h>

#include <constants.h>

#include <LogHandler.h>

namespace sloth {

void qtLogHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    spdlog::level::level_enum level{L_CRITICAL};
    std::string prefix{};
    switch (type) {
    case QtDebugMsg:
        level  = L_DEBUG;
        prefix = fmt::format(fmt::fg(fmt::terminal_color::blue), "[QT_DEBUG]");
        break;
    case QtInfoMsg:
        level  = L_INFO;
        prefix = fmt::format(fmt::fg(fmt::terminal_color::green), "[QT_INFO]");
        break;
    case QtWarningMsg:
        level  = constants::DEBUG_MODE ? L_WARN : L_DEBUG;
        prefix = fmt::format(fmt::fg(fmt::terminal_color::yellow), "[QT_WARNING]");
        break;
    case QtCriticalMsg:
        level  = L_CRITICAL;
        prefix = fmt::format(fmt::fg(fmt::terminal_color::red), "[QT_CRITICAL]");
        break;
    case QtFatalMsg:
        level  = L_CRITICAL;
        prefix = fmt::format(fmt::fg(fmt::terminal_color::bright_red), "[QT_FATAL]");
    }
    auto value_or = [](const char* value, const char* or_value) { return value != nullptr ? value : or_value; };
    LOG(level, "{}: {} ({}:{}, {})", prefix, msg, value_or(context.file, "<file>"), context.line,
        value_or(context.function, "<function>"));
    if (type == QtFatalMsg) {
        abort();
    }
}

}  // namespace sloth