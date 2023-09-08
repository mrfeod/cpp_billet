#pragma once

#include <QString>

#include <fmt/format.h>

template <>
struct fmt::formatter<QString> : formatter<string_view>
{
    auto format(const QString& s, format_context& ctx)
    {
        return formatter<string_view>::format({s.toUtf8(), static_cast<size_t>(s.size())}, ctx);
    }
};
