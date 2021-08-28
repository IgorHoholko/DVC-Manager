#include <inotify-cpp/NotifierBuilder.h>

#include <filesystem>

#include "src/core/Listener.h"
#include "src/entities/DVCEvent.h"

#include <chrono>
#include <iostream>
#include <queue>
#include <thread>


int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "Usage: ./inotify_example /path/to/dir" << std::endl;
        exit(0);
    }

    // Parse the directory to watch
    std::filesystem::path path(argv[1]);

    std::queue<dvc_listener::DVCEvent> message_quee;

    auto listener = dvc_listener::Listener(path, message_quee, ".dir").init();


    // The event loop is started in a separate thread context.
    std::thread thread([&]() { listener.run(); });

    // Terminate the event loop after 60 seconds
    std::this_thread::sleep_for(std::chrono::hours(60));
    listener.stop();
    thread.join();
    return 0;
}