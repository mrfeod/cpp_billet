#include <memory>

#include <QApplication>
#include <QDateTime>
#include <QProcess>
#include <QTimer>

#include <utils/logging/log.h>
#include <utils/random.h>

#include <constants.h>

#include <app/ui/QMLWindow.h>

#include <app/App.h>

namespace sloth {

App::App(QObject* parent) : QObject(parent) {}

App::~App() = default;

bool App::loadUI()
{
    if (ui) {
        return false;
    }

    ui = std::make_unique<QMLWindow>();

    if (!ui->load()) {
        return false;
    }

    ui->show();

    return true;
}

}  // namespace sloth
