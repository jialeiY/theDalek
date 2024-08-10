#ifndef __INTENTS_TOPICS_MOTION_PLANNING_DEBUG_TOPIC_H__
#define __INTENTS_TOPICS_MOTION_PLANNING_DEBUG_TOPIC_H__

#include <cstdint>
#include "data/defs/waypoint.h"

namespace cooboc {
namespace intent {

struct MotionPlanningDebugTopic {
    static constexpr std::size_t kWaypointNumber {500U};

    std::size_t numberOfWaypoints {0U};
    data::Waypoint waypoints[kWaypointNumber];
};

}    // namespace intent
}    // namespace cooboc

#endif
