#include <QCryptographicHash>

#include <utils/logging/log.h>
#include <utils/logging/format/Qt.h>

#include <RunGuard.h>

namespace {

QString generateKeyHash(const QString& key, const QString& salt)
{
    QByteArray data;
    data.append(key.toUtf8());
    data.append(salt.toUtf8());
    data = QCryptographicHash::hash(data, QCryptographicHash::Sha1).toHex();
    return data;
}

}  // namespace

namespace sloth {

RunGuard::RunGuard(const QString& key)
    : key(key)
    , memLockKey(generateKeyHash(key, "_memLockKey"))
    , sharedmemKey(generateKeyHash(key, "_sharedmemKey"))
    , sharedMem(sharedmemKey)
    , memLock(memLockKey, 1)
{
    memLock.acquire();
    {
        QSharedMemory fix(sharedmemKey);  // Fix for *nix: http://habrahabr.ru/post/173281/
        fix.attach();
    }
    memLock.release();
}

RunGuard::~RunGuard() { release(); }

bool RunGuard::isAnotherRunning()
{
    if (sharedMem.isAttached()) {
        return false;
    }

    memLock.acquire();
    const bool isRunning = sharedMem.attach();
    if (isRunning) {
        sharedMem.detach();
    }
    memLock.release();
    return isRunning;
}

bool RunGuard::tryToRun()
{
    if (isAnotherRunning()) {
        return false;
    }

    memLock.acquire();
    const bool result = sharedMem.create(sizeof(quint64));
    memLock.release();
    if (!result) {
        release();
        LOG(L_ERROR, "QSharedMemory::create failed: {}", sharedMem.errorString());
        return false;
    }
    return true;
}

void RunGuard::release()
{
    memLock.acquire();
    if (sharedMem.isAttached()) {
        sharedMem.detach();
    }
    memLock.release();
}

}  // namespace sloth
