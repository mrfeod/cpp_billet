#include <chrono>
#include <memory>
#include <numeric>

#include <QApplication>
#include <QFontDatabase>
#include <QtQml>

#include <constants.h>

#include <utils/logging/log.h>
#include <utils/logging/format/Qt.h>

#include <utils/enum.h>

#include <app/ui/QMLWindow.h>

namespace sloth {

QMLWindow::~QMLWindow() = default;

bool QMLWindow::load()
{
    if (isLoaded()) {
        return true;
    }

    const QString fontPath{":/fonts/RobotoMono-Medium.ttf"};
    int id = QFontDatabase::addApplicationFont(fontPath);
    if (id == -1) {
        LOG(L_CRITICAL, "Can't load font from {}", fontPath);
        return false;
    }
    QString font = QFontDatabase::applicationFontFamilies(id).at(0);
    QApplication::setFont(QFont{font});

    // qmlRegisterType<Model>("model", 1, 0, "Model");
    // qmlRegisterUncreatableType<CppModel>("cppmodel", 1, 0, "CppModel", "CppModel should not be created in QML");

    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("App", this);
    for (auto& [name, ptr] : contextObject) {
        ctx->setContextProperty(name, ptr);
    }

    // QStringLiteral could not be moved automatically: performance issue fixed in Qt 5.15
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));  // NOLINT(performance-no-automatic-move)
    if (engine.rootObjects().isEmpty()) {
        LOG_MSG(L_CRITICAL, "Can't load GUI");
        return false;
    }

    QObject* rootObject = engine.rootObjects().first();
    window              = qobject_cast<QWindow*>(rootObject);
    if (window == nullptr) {
        LOG_MSG(L_CRITICAL, "Can't find root window");
        return false;
    }

    constexpr int guiX = 0;
    constexpr int guiY = 0;
    constexpr int guiW = 1024;
    constexpr int guiH = 768;
    window->setGeometry(guiX, guiY, guiW, guiH);
    window->hide();

    return true;
}

bool QMLWindow::isLoaded() const { return window != nullptr; }

void QMLWindow::show()
{
    if (!isLoaded()) {
        return;
    }

    window->show();
    window->raise();
}

void QMLWindow::hide()
{
    if (isLoaded()) {
        window->hide();
    }
}

void QMLWindow::addContextObject(const QString& name, QObject* object) { contextObject.append({name, object}); }

}  // namespace sloth
