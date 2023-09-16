#include <csignal>

#include <QApplication>
#include <QCommandLineParser>
#include <QGuiApplication>
#include <QNetworkInterface>

#ifdef SLOTH_DEBUG
#include <QQmlDebuggingEnabler>
#endif

#include <fmt/format.h>
#include <fmt/color.h>

#include <constants.h>

#include <utils/enum.h>
#include <utils/logging/log.h>
#include <utils/qt/RunGuard.h>

#include <app/LogHandler.h>
#include <app/App.h>

struct Args
{
    spdlog::level::level_enum logLevel{sloth::constants::DEBUG_MODE ? L_DEBUG : L_INFO};
};

Args parseArgs(const QApplication& app)
{
    Args args;
    using LogLevel = decltype(args.logLevel);

    QCommandLineParser parser;
    parser.setApplicationDescription("App");
    parser.addVersionOption();
    parser.addHelpOption();

    // --- Log level ---
    QString description      = "Set application log level: ";
    const auto logLevelNames = sloth::util::enum_names<LogLevel>();
    for (auto name = logLevelNames.begin(); name != std::prev(logLevelNames.end()); name = std::next(name)) {
        description.append(fmt::format("{}={}, ", *name, std::distance(logLevelNames.begin(), name)).data());
    }
    description.chop(2);
    QCommandLineOption logLevelOpt({"l", "log_level"}, description, "level", QString::number(args.logLevel));
    logLevelOpt.setFlags(QCommandLineOption::HiddenFromHelp);
    parser.addOption(logLevelOpt);

    // --- Parsing ---
    parser.process(app);

    // --- Log level check ---
    if (parser.isSet(logLevelOpt)) {
        args.logLevel = sloth::util::enum_value<LogLevel>(parser.value(logLevelOpt).toULongLong());
    }
    return args;
}

void sighandler(int signum)
{
    switch (signum) {
    case SIGTERM:
    case SIGINT:
#ifdef WIN32
        LOG(L_INFO, "Closing the app by signal {}", signum);
#else
        LOG(L_INFO, "Closing the app by signal {}", strsignal(signum));  // NOLINT(concurrency-mt-unsafe)
#endif
        QApplication::quit();
    }
}

void initSigHandlers()
{
    for (auto signum : {SIGTERM, SIGINT}) {
        signal(signum, sighandler);
    }
}

QString createHardwareKey()
{
    static const QString key = [] {
        QString key{};
        for (const auto& netInterface : QNetworkInterface::allInterfaces()) {
            if (!(netInterface.flags() & QNetworkInterface::IsLoopBack)) {
                key = netInterface.hardwareAddress();
                break;
            }
        }
        return key.isEmpty() ? "DE:AD:BE:EF:FE:0D" : key;
    }();
    return key;
}

/**
 * @brief Load resources from static library sloth::resources
 * 
 */
struct QtResources
{
    QtResources() { Q_INIT_RESOURCE(resources); }
    ~QtResources() { Q_CLEANUP_RESOURCE(resources); }

    QtResources(const QtResources&)  = delete;
    QtResources(const QtResources&&) = delete;

    void operator=(const QtResources&)  = delete;
    void operator=(const QtResources&&) = delete;
};
static const QtResources resources;

int main(int argc, char* argv[])
{
    int exitCode = -1;

    try {
        initSigHandlers();

#ifdef SLOTH_DEBUG
        QQmlDebuggingEnabler qmlDebuggingEnabler;
#endif

        qInstallMessageHandler(sloth::qtLogHandler);

        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QCoreApplication::setApplicationName("App");
        QCoreApplication::setApplicationVersion("1.0.0");
        QApplication qapp(argc, argv);

        Args parsedArgs = parseArgs(qapp);
        sloth::logging::Logger::Instance().SetLogLevel(parsedArgs.logLevel);
        LOG(L_DEBUG, "Log level set to {}", sloth::util::enum_name(parsedArgs.logLevel));

        sloth::RunGuard guard(createHardwareKey());
        if (!guard.tryToRun()) {
            LOG_MSG(L_ERROR, "Another instance is running");
            return exitCode;
        }

        sloth::App app;
        if (!app.loadUI()) {
            LOG_MSG(L_ERROR, "Failed to load UI");
            return exitCode;
        }

        exitCode = QApplication::exec();
    }
    catch (const std::exception& ex) {
        LOG(L_CRITICAL, "Unhandled exception: {}", ex.what());
        throw;
    }
    catch (...) {
        LOG_MSG(L_CRITICAL, "Unhandled unknown exception");
        throw;
    }

    return exitCode;
}
