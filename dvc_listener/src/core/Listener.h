#pragma once

#include "../entities/DVCEvent.h"
#include <inotify-cpp/NotifierBuilder.h>
#include <queue>
#include <string>

namespace dvc_listener {

    class Listener {
    public:
        Listener(const std::filesystem::path& path, std::queue<DVCEvent>& message_quee, const std::string& watch_extention);

        inotify::NotifierBuilder init();

        const std::initializer_list<inotify::Event> events = {inotify::Event::create, inotify::Event::move};


    private:
        std::filesystem::path _path;
        std::queue<DVCEvent>  _message_quee;
        std::string           _watch_extention;
    };
}// namespace dvc_listener