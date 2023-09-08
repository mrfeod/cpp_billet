#pragma once

#include <string>

#include <QString>

namespace sloth::constants {

#ifdef SLOTH_DEBUG
constexpr bool DEBUG_MODE = true;
#else
constexpr bool DEBUG_MODE = false;
#endif

}  // namespace sloth::constants

// WORKAROUND
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
#include <functional>      // std::hash
#include <QHashFunctions>  // qHash

template <>
struct std::hash<QString>
{
    std::size_t operator()(QString const& s) const noexcept { return qHash(s); }
};
#endif  // QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
