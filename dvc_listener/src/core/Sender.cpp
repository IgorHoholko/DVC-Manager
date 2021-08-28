#include "Sender.h"


namespace dvc_listener {

    Sender::Sender(const std::string& url, const MessageQueueMetaPtr& message_quee_meta, const std::string& username,
                   const std::string& password, std::chrono::seconds sleep_interval)
        : url(url)
        , _client(U(url))
        , _username(username)
        , _password(password)
        , _sleep_interval(sleep_interval) {
        this->_message_quee_meta = message_quee_meta;
        this->_auth();
    }

    void Sender::_auth() {

        bool success = false;
        while (!success) {
            try {
                auto response = pplx::create_task([this]() {
                                    json::value jsonObject;
                                    jsonObject[U("username")] = json::value::string(U(this->_username));
                                    jsonObject[U("password")] = json::value::string(U(this->_password));

                                    return this->_client.request(methods::POST,
                                                                 uri_builder(U("api")).append_path(U("auth/login")).to_string(),
                                                                 jsonObject.serialize(), U("application/json"));
                                })
                                        .then([](http_response response) {
                                            if (response.status_code() != 200) {
                                                throw std::runtime_error("Returned " + std::to_string(response.status_code()));
                                            }
                                            return response.extract_json();
                                        })
                                        .then([](json::value jsonObject) {
                                            return jsonObject[U("access_token")].as_string();
                                        });

                this->_token = response.get();
                success      = true;
            } catch (const std::runtime_error& error) {
                std::cerr << "Failed to login!" << std::endl
                          << error.what() << std::endl
                          << "Trying again in 2 seconds.." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
        std::cout << this->_token << std::endl;
    }

    bool Sender::_sendDVCMeta(const DVCMeta& meta){
        return true;
    }

    void Sender::run() {
        while (true) {
            // TODO:Stop
            if (!this->_message_quee_meta->empty()) {
                bool is_sent = this->_sendDVCMeta(this->_message_quee_meta->front());
                if (is_sent) {
                    this->_message_quee_meta->pop();
                }
            }

            std::this_thread::sleep_for(this->_sleep_interval);
        }
    }

}// namespace dvc_listener
