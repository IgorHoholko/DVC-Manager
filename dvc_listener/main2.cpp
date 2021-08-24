

#include "src/core/Sender.h"

#include <queue>

#include "src/entities/DVCEvent.h"

int main(int argc, char** argv) {
    // Create a file stream to write the received file into it.
    // http_client client(U("http://localhost:5000"));
    // auto        get_r = client.request(methods::GET, uri_builder(U("api")).append_path(U("datasets/")).to_string());

    // std::cout << get_r.get().status_code() << std::endl;
    // std::cout << get_r.get().to_string() << std::endl;

    // json::value jsonObject;
    // jsonObject[U("username")] = json::value::string(U("ihoholko"));
    // jsonObject[U("password")] = json::value::string(U("12321"));

    // auto post_r = client.request(methods::POST,
    //                              uri_builder(U("api")).append_path(U("auth/login")).to_string(),
    //                              jsonObject.serialize(), U("application/json"));

    // auto post_r_json = post_r.get().extract_json();

    // std::cout << post_r_json.get()[U("access_token")].as_string() << ")" << std::endl;


    if (argc <= 2) {
        std::cout << "Usage: ./requester username password" << std::endl;
        exit(0);
    }

    auto username = argv[1];
    auto password = argv[2];

    std::cout << username << password << std::endl;

    std::queue<dvc_listener::DVCEvent> message_quee;

    auto sender = dvc_listener::Sender("http://localhost:5000", message_quee, username, password);

    return 0;
}