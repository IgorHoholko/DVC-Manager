#pragma once

#include "../utils/common.h"
#include "IWorker.h"
#include <inotify-cpp/NotifierBuilder.h>
#include <queue>
#include <string>


namespace dvc_listener {

    class Listener: public IWorker{
    public:
        Listener(const std::filesystem::path& path, const MessageQueueEventsPtr& message_quee_events, const std::string& watch_extention);

        void init() override;
        void run() override;
        void stop() override;

    public:
        const std::initializer_list<inotify::Event> events_to_listen = {inotify::Event::create, inotify::Event::move};

    private:
        MessageQueueEventsPtr _message_quee_events;

        inotify::NotifierBuilder _notifier;

        std::filesystem::path _path;
        std::queue<DVCEvent>  _message_quee;
        std::string           _watch_extention;
    };
}// namespace dvc_listener