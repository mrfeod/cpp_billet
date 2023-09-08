#pragma once

#include <QObject>
#include <QPointer>
#include <QQmlApplicationEngine>
#include <QWindow>

namespace sloth {

class QMLWindow final : public QObject
{
    Q_OBJECT

public:
    QMLWindow() = default;
    ~QMLWindow() final;

    QMLWindow(const QMLWindow&) = delete;
    QMLWindow& operator=(const QMLWindow&) = delete;

    bool load();
    bool isLoaded() const;

    void show();
    void hide();

    void addContextObject(const QString& name, QObject* object);

private:
    QQmlApplicationEngine engine;
    QVector<QPair<QString, QPointer<QObject>>> contextObject;
    QPointer<QWindow> window;
};

}  // namespace sloth
