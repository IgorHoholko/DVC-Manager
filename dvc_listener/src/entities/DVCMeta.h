#pragma once

#include <chrono>
#include <inotify-cpp/Event.h>

#include <map>
#include <set>
#include <string>
#include <vector>


namespace dvc_listener {

    using str_counter = std::map<std::string, size_t>;

    struct DVCMeta {
        std::string                           path_meta;
        std::chrono::steady_clock::time_point time;

        std::map<std::string, str_counter> ext_counter;// {"dataset1": {".jpg": 200, ".xml": 20}, ...}


        std::set<std::string> datasets;
    };
}// namespace dvc_listener