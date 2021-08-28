#pragma once

#include <chrono>
#include <filesystem>

namespace dvc_listener {

    struct DVCEvent {
        std::filesystem::path                 path;
        std::chrono::steady_clock::time_point time;
    };
}// namespace dvc_listener