

#include "src/core/Sender.h"

#include <queue>

#include "src/entities/DVCEvent.h"

#include "src/utils/common.h"

using namespace dvc_listener;

int main(int argc, char** argv) {


    if (argc <= 2) {
        std::cout << "Usage: ./requester username password" << std::endl;
        exit(0);
    }

    auto username = argv[1];
    auto password = argv[2];

    std::cout << username << password << std::endl;

    MessageQueueMetaPtr message_quee_meta(new MessageQueueMeta());

    auto sender = dvc_listener::Sender("http://localhost:5000", message_quee_meta, username, password, std::chrono::seconds(1));

    return 0;
}