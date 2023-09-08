#include <utils/random.h>

#include <cassert>
#include <random>

namespace sloth::util {

int randomInt(int max /*= std::numeric_limits<int>::max()*/, int min /* = 0 */)
{
    assert(max > min && "Maximum value must be greater than minimum");

    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> uniform(min, max);
    return uniform(generator);
}

}  // namespace sloth::util