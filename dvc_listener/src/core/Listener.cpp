#include "Listener.h"

namespace dvc_listener {

    Listener::Listener(const std::filesystem::path& path, std::queue<DVCEvent>& message_quee, const std::string& watch_extention)
        : _path(path)
        , _watch_extention(watch_extention) {
        this->_message_quee = message_quee;
    }

    inotify::NotifierBuilder Listener::init() {
        auto handleNotification = [&](const inotify::Notification& notification) {
            std::cout << "Try.." << std::endl;
            if (notification.path.has_extension() && notification.path.extension() == this->_watch_extention) {
                std::cout << "\tCatched! " << notification.path << std::endl;
                this->_message_quee.push(DVCEvent{notification.path, notification.time});

            }
        };

        auto notifier = inotify::BuildNotifier()
                                .watchPathRecursively(this->_path)
                                .onEvents(this->events, handleNotification);
        return notifier;
    }
}// namespace dvc_listener