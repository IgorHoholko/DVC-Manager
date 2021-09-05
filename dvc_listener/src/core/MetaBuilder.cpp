#include "MetaBuilder.h"

namespace dvc_listener {

    MetaBuilder::MetaBuilder(const std::filesystem::path& path_dvc_storage, const MessageQueueEventsPtr& message_queue_events,
                             const MessageQueueMetaPtr& message_queue_meta, std::chrono::seconds sleep_interval)
        : path_dvc_storage(path_dvc_storage)
        , _message_queue_events(message_queue_events)
        , _message_queue_meta(message_queue_meta)
        , sleep_interval(sleep_interval) {}

    void MetaBuilder::init() {}

    void MetaBuilder::run() {
        DVCMeta meta;
        while (true) {
            if (this->_stop) {
                this->_stop = false;
                return;
            }

            if (!this->_message_queue_events->empty()) {
                auto event = this->_message_queue_events->front();

                meta = this->parse(event);// TODO: Check for big files delay

                this->_message_queue_meta->push(meta);
                this->_message_queue_meta->pop();
            }

            std::this_thread::sleep_for(this->sleep_interval);
        }
    }

    void MetaBuilder::stop() {
        this->_stop = true;
    }


    DVCMeta MetaBuilder::parse(const DVCEvent& event) {
        DVCMeta meta;

        std::ifstream fin(event.path.string(), std::ios::in);

        if (!fin.is_open()) {
            std::stringstream msg;
            msg << "Failed to open " << event.path.string() << "!";
            throw std::runtime_error(msg.str());
        }

        std::unordered_set<std::string>              datasets;
        std::unordered_map<std::string, str_counter> counter;

        char s;
        char trash_buf[500];
        char realpath[500];
        char md5[50];

        std::string str;
        std::string dataset, extention;

        while (!fin.eof()) {
            fin >> s;

            if (s == '"' && fin.peek() == 'm') {
                fin >> trash_buf >> s;
                fin.get(md5, 33);
                fin >> trash_buf;
            }
            if (s == '"' && fin.peek() == 'r') {
                fin >> trash_buf >> s;

                fin.get(realpath, 500, '"');

                std::tie(dataset, extention) = this->_extractDatasetAndExtention(realpath);

                meta.datasets.emplace(dataset);
                ++meta.ext_counter[dataset][extention];
            }
        }

        meta.path_meta   = event.path;
        meta.time        = event.time;

        fin.close();

        for (auto da : datasets) {
            std::cout << da << ":" << std::endl;
            for (auto t : counter[da]) {
                std::cout << " " << t.first << " " << t.second << std::endl;
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;

        return meta;
    }

    std::tuple<std::string, std::string> MetaBuilder::_extractDatasetAndExtention(const std::string& rp) {
        std::string dataset = "";
        std::string ext     = "";

        auto slash_pos = rp.find("/");

        bool is_dataset = slash_pos != rp.npos && slash_pos + 1 != rp.size();// exclude 'fake' and 'fake/'
        if (!is_dataset) return std::tie(dataset, ext);

        dataset = rp.substr(0, slash_pos);

        auto back_slash_pos = rp.rfind("/");
        auto ext_pos        = rp.rfind(".");

        ext = (ext_pos < back_slash_pos || ext_pos == rp.npos) ? "" : rp.substr(ext_pos, rp.size());
        return std::tie(dataset, ext);
    }


    //     json::value jsonify(const DVCMeta& meta);


}// namespace dvc_listener