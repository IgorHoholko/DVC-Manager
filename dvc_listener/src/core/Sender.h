#pragma once

#include <cpprest/filestream.h>
#include <cpprest/http_client.h>

#include <cpprest/containerstream.h>       // Async streams backed by STL containers
#include <cpprest/http_listener.h>         // HTTP server
#include <cpprest/interopstream.h>         // Bridges for integrating Async streams with STL and WinRT streams
#include <cpprest/json.h>                  // JSON library
#include <cpprest/producerconsumerstream.h>// Async streams for producer consumer scenarios
#include <cpprest/rawptrstream.h>          // Async streams backed by raw pointer to memory
#include <cpprest/uri.h>                   // URI library
#include <cpprest/ws_client.h>             // WebSocket client


using namespace utility;             // Common utilities like string conversions
using namespace web;                 // Common features like URIs.
using namespace web::http;           // Common HTTP functionality
using namespace web::http::client;   // HTTP client features
using namespace concurrency::streams;// Asynchronous streams

using namespace web::http::experimental::listener;     // HTTP server
using namespace web::experimental::web_sockets::client;// WebSockets client
using namespace web::json;                             // JSON library

#include <queue>
#include <thread>


#include "../entities/DVCEvent.h"
#include "../utils/common.h"
#include "IWorker.h"


namespace dvc_listener {

    class Sender : public IWorker {
    public:
        Sender(const std::string& url, const MessageQueueMetaPtr& message_quee_meta, const std::string& username,
               const std::string& password, std::chrono::seconds sleep_interval);

        void init() override;
        void run() override;
        void stop() override;

    private:
        bool _sendDVCMeta(const DVCMeta& meta);

        void _auth();

    public:
        const std::string url;
        std::chrono::seconds sleep_interval;

    private:
        MessageQueueMetaPtr _message_quee_meta;

        bool _stop = false;

        std::string _username;
        std::string _password;

        std::string _token;

        http_client _client;
    };

}// namespace dvc_listener