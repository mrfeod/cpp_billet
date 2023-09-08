#pragma once

#include <QJsonObject>

namespace sloth::util {

enum class SettingType
{
    Unsigned,
    Signed
};

enum class SettingsStatus
{
    Ok,
    Broken,
    Empty,
};

bool saveSettings(const QString& filePath, const QString& name, QJsonObject value,
                  SettingType type = SettingType::Unsigned);

std::pair<QJsonObject, SettingsStatus> loadSettings(const QString& filePath, const QString& name,
                                                    SettingType type = SettingType::Unsigned);

}  // namespace sloth::util