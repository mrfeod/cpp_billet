#include <QEventLoop>
#include <QTimer>

#include <utils/qt/slumber.h>

namespace sloth::util {

void slumber(int msec)
{
    if (msec <= 0) {
        return;
    }

    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

}  // namespace sloth::util
