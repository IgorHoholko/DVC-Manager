#include "Listener.h"

namespace dvc_listener {

    Listener::Listener(const std::filesystem::path& path, const MessageQueueEventsPtr& message_quee_events, const std::string& watch_extention)
        : _path(path)
        , _watch_extention(watch_extention) {
        this->_message_quee_events = message_quee_events;
    }

    void Listener::init() {
        auto handleNotification = [&](const inotify::Notification& notification) {
            std::cout << "Try.." << std::endl;
            if (notification.path.has_extension() && notification.path.extension() == this->_watch_extention) {
                std::cout << "\tCatched! " << notification.path << std::endl;
                this->_message_quee_events->push({notification.path, notification.time});
            }
        };

        this->_notifier = inotify::BuildNotifier()
                                .watchPathRecursively(this->_path)
                                .onEvents(this->events_to_listen, handleNotification);
    }

    void Listener::run(){
        this->_notifier.run();
    }

    void Listener::stop(){
        this->_notifier.stop();
    }
}// namespace dvc_listener