#include <inotify-cpp/NotifierBuilder.h>
#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <queue>
#include <thread>

#include "../Listener.h"
#include "../Sender.h"
#include "../MetaBuilder.h"

#include "../../entities/DVCEvent.h"
#include "../../entities/DVCMeta.h"



int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "Usage: path to config.yaml" << std::endl;
        exit(0);
    }

    try{
        std::string username = std::getenv("username");
        std::string password = std::getenv("password");
        std::cout <<  username << " " << password << std::endl;
    }catch (const std::logic_error& err){
        std::cerr << "Set 'username' and 'password' into your enviroment!" << std::endl;
        exit(0);
    }
    

    std::filesystem::path path(argv[1]);

    YAML::Node config = YAML::LoadFile(path.c_str());

    if (config["myname"]) {
        std::cout << "Last logged in: " << config["myname"].as<std::string>() << std::endl;
    }

    return 0;
}