#pragma once



#include <cpprest/json.h>
#include <iostream>
#include <filesystem>

#include <tuple>
#include <unordered_set>
#include <map>
#include <unordered_map>


#include "../entities/DVCEvent.h"
#include "../entities/DVCMeta.h"


using namespace web; 
using namespace web::json; 

namespace dvc_listener {


    class MetaBuilder {
    public:
        MetaBuilder(const std::filesystem::path& path_dvc_storage);

        DVCMeta parse(const DVCEvent& event);

        json::value jsonify(const DVCMeta& meta);

    public:
        
        const std::filesystem::path path_dvc_storage;

    private:

        std::tuple<std::string, std::string> _extractDatasetAndExtention(const std::string& rp);

    };


}// namespace dvc_listener