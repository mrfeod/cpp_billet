#include <QCryptographicHash>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>

#include <utils/logging/log.h>
#include <utils/logging/format/Qt.h>

#include <hash.h>
#include <settings.h>

namespace sloth::util {

namespace {

QString calculateSign(const QJsonObject& object)
{
    static const QString salt = QByteArray("64a2041f-a7d5-4fad-80a2-9fc1eee2ebb8").toBase64();
    QString doc               = QJsonDocument(object).toJson(QJsonDocument::Compact);
    return calculateHash(QString(doc + salt).toLatin1());
}

bool checkSign(QJsonObject settings)
{
    QString sign = settings.take("sign").toString();
    return sign == calculateSign(settings);
}

}  // namespace

bool saveSettings(const QString& filePath, const QString& name, QJsonObject value,
                  SettingType type /*  = SettingType::Unsigned */)
{
    QJsonObject content;

    QFile file(filePath);
    if (file.open(QFileInfo(filePath).exists() ? QIODevice::ReadOnly : QIODevice::ReadWrite)) {
        content = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
        LOG(L_DEBUG, "Opened {} file contains {} settings", filePath, content.size());
    } else {
        LOG(L_ERROR, "Can't open file {} to read settings", filePath);
        return false;
    }

    if (type == SettingType::Signed) {
        QString sign = calculateSign(value);
        value.insert("sign", sign);
    }
    content[name] = value;

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        LOG(L_ERROR, "Can't open file {} to write settings", filePath);
        return false;
    }
    return file.write(QJsonDocument(content).toJson(QJsonDocument::Compact)) >= 0;
}

std::pair<QJsonObject, SettingsStatus> loadSettings(const QString& filePath, const QString& name,
                                                    SettingType type /*  = SettingType::Unsigned */)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        LOG(L_DEBUG, "Can't open {} file with settings", filePath);
        return {{}, SettingsStatus::Empty};
    }

    QJsonObject content = QJsonDocument::fromJson(file.readAll()).object();
    if (!content.contains(name)) {
        return {{}, SettingsStatus::Empty};
    }

    QJsonObject settings = content[name].toObject();
    if (type == SettingType::Signed && !checkSign(settings)) {
        return {{}, SettingsStatus::Broken};
    }

    return {settings, SettingsStatus::Ok};
}
}  // namespace sloth::util