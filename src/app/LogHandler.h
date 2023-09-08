#pragma once

#include <QMessageLogContext>

namespace sloth {

void qtLogHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

}