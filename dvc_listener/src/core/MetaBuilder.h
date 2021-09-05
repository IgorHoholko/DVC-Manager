#pragma once


#include <cpprest/json.h>
#include <filesystem>
#include <iostream>

#include <map>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <thread>

#include "IWorker.h"
#include "../entities/DVCEvent.h"
#include "../entities/DVCMeta.h"
#include "../utils/common.h"


using namespace web;
using namespace web::json;

namespace dvc_listener {


    class MetaBuilder : IWorker {
    public:
        MetaBuilder(const std::filesystem::path& path_dvc_storage, const MessageQueueEventsPtr& message_queue_events,
                    const MessageQueueMetaPtr& message_queue_meta, std::chrono::seconds sleep_interval);

        void init() override;
        void run() override;
        void stop() override;

        DVCMeta parse(const DVCEvent& event);

        json::value jsonify(const DVCMeta& meta);
    
    private:
        std::tuple<std::string, std::string> _extractDatasetAndExtention(const std::string& rp);
        bool _stop = false;

    public:
        const std::filesystem::path path_dvc_storage;
        const std::chrono::seconds sleep_interval;
    
    private:
        MessageQueueEventsPtr _message_queue_events;
        MessageQueueMetaPtr _message_queue_meta;
    };


}// namespace dvc_listener