#pragma once

#ifdef MAGIC_ENUM_RANGE_MIN
#undef MAGIC_ENUM_RANGE_MIN
#endif
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define MAGIC_ENUM_RANGE_MIN -256

#ifdef MAGIC_ENUM_RANGE_MAX
#undef MAGIC_ENUM_RANGE_MAX
#endif
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define MAGIC_ENUM_RANGE_MAX 256

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#include <magic_enum.hpp>
#pragma GCC diagnostic pop
#ifndef MAGIC_ENUM_SUPPORTED_ALIASES
static_assert(false, "magic_enum do not support aliases and now you have undefined behavior for magic_enum casting");
#endif

namespace sloth::util {
using namespace magic_enum;
}
