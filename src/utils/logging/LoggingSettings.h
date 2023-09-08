#pragma once

#include <utils/logging/log_common.h>

namespace sloth::logging {

class LoggingSettings
{
public:
    enum class SyncMode
    {
        Sync,
        Async
    };

    void SetBacktraceSize(size_t value) { backtrace_size_ = value; }
    void SetSyncMode(SyncMode value) { sync_mode_ = value; }

    size_t GetBacktraceSize() const noexcept { return backtrace_size_; }
    SyncMode GetSyncMode() const noexcept { return sync_mode_; }

private:
    size_t backtrace_size_{1000};  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    SyncMode sync_mode_{SyncMode::Async};
};

}  // namespace sloth::logging
