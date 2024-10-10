#ifndef __INTENTS_TOPICS_REFERENCE_PATH_TOPIC_H__
#define __INTENTS_TOPICS_REFERENCE_PATH_TOPIC_H__


#include <cstdint>
#include "data/defs/passing_point.h"
#include "data/defs/position2d.h"
#include "data/defs/reference_path_id.h"
#include "data/defs/route_id.h"
#include "intents/topics/common.h"

namespace cooboc {
namespace intent {


struct ReferencePathTopic {
    static constexpr std::size_t kReferencePathPointsCapacity {1000U};

    data::ReferencePathId id {data::kInvalidReferencePathId};
    data::RouteId routeId {data::kInvalidRouteId};

    std::size_t pointsNumber {0U};
    data::Position2D points[kReferencePathPointsCapacity];

    // std::size_t passingPointSize {0U};
    // data::PassingPoint passingPoint[kReferencePathPassingPointCapacity];
};

}    // namespace intent
}    // namespace cooboc

#endif
