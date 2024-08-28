#ifndef __INTENTS_TOPICS_TRAJECTORY_TOPIC_H__
#define __INTENTS_TOPICS_TRAJECTORY_TOPIC_H__


#include <cstdint>
#include "data/defs/passing_point.h"
#include "data/defs/position2d.h"
#include "data/defs/route_id.h"
#include "intents/topics/common.h"

namespace cooboc {
namespace intent {


using TrajectoryId = std::uint64_t;

struct TrajectoryTopic {
        bool hasValue {false};
    TrajectoryId trajectoryId {0U};
    std::size_t passingPointSize {0U};

    data::PassingPoint passingPoint[kTrajectoryPassingPointCapacity];

    data::RouteId routeId {0U};
};

}    // namespace intent
}    // namespace cooboc

#endif
