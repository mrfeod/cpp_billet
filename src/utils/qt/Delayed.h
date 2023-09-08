#pragma once

#include <memory>
#include <functional>

namespace sloth::util {

/**
 * @brief Object that executes function with delay and displacing.
 * 
 */
class Delayed
{
public:
    /**
     * @brief Construct a new Delayed object.
     * 
     * @return std::unique_ptr<Delayed>
     */
    static std::unique_ptr<Delayed> create();

    virtual ~Delayed() = default;

    /**
     * @brief Executes function with delay and displacing.
     * 
     * @param ms Delay in milliseconds.
     * @param f Function to execute.
     */
    virtual void exec(int ms, std::function<void()>&& f) = 0;
};

}  // namespace sloth::util
