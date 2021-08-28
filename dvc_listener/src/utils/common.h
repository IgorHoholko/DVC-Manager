#pragma once

#include <chrono>
#include "../entities/DVCEvent.h"
#include "../entities/DVCMeta.h"

#include <map>
#include <set>
#include <string>
#include <vector>
#include <queue>


namespace dvc_listener {

    using MessageQueueEvents = std::queue<DVCEvent>;
    using MessageQueueEventsPtr = std::shared_ptr<MessageQueueEvents>;

    using MessageQueueMeta = std::queue<DVCMeta>;
    using MessageQueueMetaPtr = std::shared_ptr<MessageQueueMeta>;

    

}// namespace dvc_listener