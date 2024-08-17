#ifndef __INTENTS_TOPICS_TRAJECTORY_TOPIC_H__
#define __INTENTS_TOPICS_TRAJECTORY_TOPIC_H__


#include <cstdint>
#include "data/defs/position2d.h"
#include "data/defs/route_id.h"

namespace cooboc {
namespace intent {

// WIP
struct PassingPoint {
    data::Position2D position;    // in world
    // float speed;
    //  orientation or curvature to the last segment
};

using TrajectoryId = std::size_t;

struct TrajectoryTopic {
    static constexpr std::size_t kPassingPointCapacity {1000U};
    bool hasValue {false};
    TrajectoryId trajectoryId {0U};
    std::size_t passingPointSize {0U};

    PassingPoint passingPoint[kPassingPointCapacity];

    data::RouteId routeId {0U};
};

}    // namespace intent
}    // namespace cooboc

#endif
