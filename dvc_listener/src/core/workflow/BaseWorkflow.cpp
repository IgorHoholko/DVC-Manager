#include <inotify-cpp/NotifierBuilder.h>
#include <yaml-cpp/yaml.h>

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <queue>
#include <thread>

#include "../Listener.h"
#include "../MetaBuilder.h"
#include "../Sender.h"

#include "../../entities/DVCEvent.h"
#include "../../entities/DVCMeta.h"


using namespace dvc_listener;

void parseEnv(std::string& username, std::string& password, std::string& path_dvc_storage, std::string& api_url) {
    try {
        username = std::getenv("DVC_LISTENER_USERNAME");
        password = std::getenv("DVC_LISTENER_PASSWORD");
    } catch (const std::runtime_error& err) {
        std::cerr << "Set 'DVC_LISTENER_USERNAME' and 'DVC_LISTENER_PASSWORD' into your enviroment!" << std::endl;
        exit(0);
    }
    try {
        path_dvc_storage = std::getenv("DVC_STORAGE_PATH");
    } catch (const std::runtime_error& err) {
        std::cerr << "Set 'DVC_STORAGE_PATH' into your enviroment!" << std::endl;
        exit(0);
    }
    try {
        api_url = std::getenv("API_URL");
    } catch (const std::runtime_error& err) {
        std::cerr << "Set 'API_URL' into your enviroment!" << std::endl;
        exit(0);
    }
}


int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "Usage: path to config.yaml" << std::endl;
        exit(0);
    }

    std::string username, password;
    std::string path_dvc_storage;
    std::string api_url;
    parseEnv(username, password, path_dvc_storage, api_url);


    std::filesystem::path config_path(argv[1]);
    YAML::Node            config = YAML::LoadFile(config_path.c_str());

    auto listener_watch_extention    = config["listener_watch_extention"].as<std::string>();
    auto meta_builder_sleep_interval = std::chrono::seconds(config["meta_builder_sleep_interval"].as<int>());
    auto sender_sleep_interval       = std::chrono::seconds(config["sender_sleep_interval"].as<int>());


    MessageQueueEventsPtr message_quee_events(new MessageQueueEvents());
    MessageQueueMetaPtr   message_quee_meta(new MessageQueueMeta());


    auto listener = Listener(path_dvc_storage, message_quee_events, listener_watch_extention);
    listener.init();

    auto meta_builder = MetaBuilder(path_dvc_storage, message_quee_events, message_quee_meta, meta_builder_sleep_interval);
    meta_builder.init();

    auto sender = Sender(api_url, message_quee_meta, username, password, sender_sleep_interval);
    sender.init();


    std::thread thread_listener([&]() { listener.run(); });
    std::thread thread_meta_builder([&]() { meta_builder.run(); });
    std::thread thread_sender([&]() { sender.run(); });


    listener.stop();
    thread_listener.join();

    meta_builder.stop();
    thread_meta_builder.join();

    sender.stop();
    thread_sender.join();


    return 0;
}