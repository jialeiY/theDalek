#ifndef __INTENTS_TOPICS_TRAJECTORY_TOPIC_H__
#define __INTENTS_TOPICS_TRAJECTORY_TOPIC_H__


#include <cstdint>
#include "data/defs/position2d.h"
#include "data/defs/route_id.h"

namespace cooboc {
namespace intent {


struct PassingPoint {
    data::Position2D position;    // in world
    float speed;
};

struct TrajectoryTopic {
    static constexpr std::size_t kPassingPointCapacity {1000U};


    PassingPoint passingPoint[kPassingPointCapacity];

    data::RouteId routeId {0U};
};

}    // namespace intent
}    // namespace cooboc

#endif
