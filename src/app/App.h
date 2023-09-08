#pragma once

#include <memory>

#include <QObject>

namespace sloth {

class QMLWindow;

class App final : public QObject
{
    Q_OBJECT

public:
    explicit App(QObject* parent = nullptr);
    ~App() override;

    App(const App&) = delete;
    App& operator=(const App&) = delete;

    bool loadUI();

private:
    std::unique_ptr<QMLWindow> ui;
};

}  // namespace sloth
