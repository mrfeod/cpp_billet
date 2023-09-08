#pragma once

#include <limits>

namespace sloth::util {

int randomInt(int max = std::numeric_limits<int>::max(), int min = 0);

}  // namespace sloth::util