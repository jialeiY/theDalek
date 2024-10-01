#ifndef __INTENTS_TOPICS_REFERENCE_PATH_TOPIC_H__
#define __INTENTS_TOPICS_REFERENCE_PATH_TOPIC_H__


#include <cstdint>
#include "data/defs/passing_point.h"
#include "data/defs/position2d.h"
#include "data/defs/route_id.h"
#include "intents/topics/common.h"

namespace cooboc {
namespace intent {


using ReferencePathId = std::uint64_t;

struct ReferencePathTopic {
    bool hasValue {false};
    ReferencePathId referencePathId {0U};
    std::size_t passingPointSize {0U};

    data::PassingPoint passingPoint[kReferencePathPassingPointCapacity];

    data::RouteId routeId {0U};
};

}    // namespace intent
}    // namespace cooboc

#endif
