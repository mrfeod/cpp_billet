#pragma once

namespace sloth::util {

template <class F>
struct ScopeGuard
{
    F f;
    ~ScopeGuard() { f(); }

    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard(ScopeGuard&&)      = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ScopeGuard& operator=(ScopeGuard&&) = delete;
};

template <class F>
ScopeGuard(F) -> ScopeGuard<F>;

}  // namespace sloth::util