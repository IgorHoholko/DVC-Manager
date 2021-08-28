#include "MetaBuilder.h"

namespace dvc_listener {

    MetaBuilder::MetaBuilder(const std::filesystem::path& path_dvc_storage)
        : path_dvc_storage(path_dvc_storage) {}


    std::tuple<std::string, std::string> MetaBuilder::_extractDatasetAndExtention(const std::string& rp) {
        std::string dataset = "";
        std::string ext = "";

        auto slash_pos  = rp.find("/");
        
        bool is_dataset = slash_pos != rp.npos && slash_pos + 1 != rp.size();// exclude 'fake' and 'fake/'
        if (!is_dataset) return std::tie(dataset,ext);

        dataset = rp.substr(0, slash_pos);

        auto back_slash_pos = rp.rfind("/");
        auto ext_pos        = rp.rfind(".");

        ext = (ext_pos < back_slash_pos || ext_pos == rp.npos) ? "": rp.substr(ext_pos, rp.size());
        return std::tie(dataset, ext);
    }


    DVCMeta MetaBuilder::parse(const DVCEvent& event) {
        DVCMeta meta;

        std::ifstream fin(event.path.string(), std::ios::in);

        if (!fin.is_open()) {
            std::stringstream msg;
            msg << "Failed to open " << event.path.string() << "!";
            throw std::runtime_error(msg.str());
        }

        std::unordered_set<std::string>                                          datasets;
        std::unordered_map<std::string, std::unordered_map<std::string, size_t>> counter;

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

                datasets.emplace(dataset);
                ++counter[dataset][extention];
            }
        }

        for (auto da : datasets) {
            std::cout << da << ":" << std::endl;
            for (auto t : counter[da]) {
                std::cout << " " << t.first << " " << t.second << std::endl;
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
        fin.close();


        fin.close();
    }


    //     json::value jsonify(const DVCMeta& meta);


}// namespace dvc_listener