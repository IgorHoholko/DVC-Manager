#include <inotify-cpp/NotifierBuilder.h>

#include <filesystem>

#include "src/core/MetaBuilder.h"
#include "src/entities/DVCEvent.h"

#include <chrono>
#include <iostream>
#include <queue>
#include <thread>


int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "Usage: specify .dir" << std::endl;
        exit(0);
    }

    // Parse the directory to watch
    std::filesystem::path path(argv[1]);

    dvc_listener::DVCEvent event{ path, std::chrono::steady_clock::now()};


    auto meta_builder = dvc_listener::MetaBuilder(path);
    meta_builder.parse(event);

    return 0;
}