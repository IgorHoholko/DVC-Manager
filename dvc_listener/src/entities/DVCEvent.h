#pragma once

#include <chrono>
#include <filesystem>
#include <inotify-cpp/Event.h>

namespace dvc_listener {

    struct DVCEvent {
        std::filesystem::path                 path;
        std::chrono::steady_clock::time_point time;
        inotify::Event                        event;
    };
}// namespace dvc_listener