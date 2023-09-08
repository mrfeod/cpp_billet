#include <QCryptographicHash>

#include <hash.h>

namespace sloth::util {

QString calculateHash(const QString& str)
{
    if (str.isEmpty()) {
        return {};
    }
    return QCryptographicHash::hash(str.toLatin1(), QCryptographicHash::Algorithm::Sha256).toBase64();
}

}  // namespace sloth::util