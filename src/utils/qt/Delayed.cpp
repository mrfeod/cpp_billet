#include <QTimer>

#include <Delayed.h>

namespace sloth::util {

struct DelayedImpl final : public Delayed
{
    void exec(int ms, std::function<void()>&& f) override
    {
        timer.setSingleShot(true);
        QObject::disconnect(connection);
        connection = timer.callOnTimeout([this, call = std::move(f)] {
            QObject::disconnect(connection);
            call();
        });
        timer.start(ms);
    }

    QTimer timer;
    QMetaObject::Connection connection;
};

std::unique_ptr<Delayed> Delayed::create() { return std::make_unique<DelayedImpl>(); }

}  // namespace sloth::util
