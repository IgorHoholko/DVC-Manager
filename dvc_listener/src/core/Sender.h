#pragma once

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>                       // JSON library
#include <cpprest/uri.h>                        // URI library
#include <cpprest/ws_client.h>                  // WebSocket client
#include <cpprest/containerstream.h>            // Async streams backed by STL containers
#include <cpprest/interopstream.h>              // Bridges for integrating Async streams with STL and WinRT streams
#include <cpprest/rawptrstream.h>               // Async streams backed by raw pointer to memory
#include <cpprest/producerconsumerstream.h>     // Async streams for producer consumer scenarios


using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

using namespace web::http::experimental::listener;          // HTTP server
using namespace web::experimental::web_sockets::client;     // WebSockets client
using namespace web::json;                                  // JSON library

#include <thread>
#include <queue>


#include "../entities/DVCEvent.h"


namespace dvc_listener{

    class Sender{
    public:
        Sender(const std::string& url, std::queue<DVCEvent>& message_quee, const std::string& username, const std::string& password );

        bool run();

        const std::string url;

    private:

        bool _sentDVCEvent(DVCEvent&& event);

        void _auth();

    private:

        std::string _username;
        std::string _password;

        std::string _token;

        http_client _client;

    };

}