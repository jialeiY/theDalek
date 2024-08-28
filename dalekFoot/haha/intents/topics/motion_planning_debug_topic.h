#ifndef __INTENTS_TOPICS_MOTION_PLANNING_DEBUG_TOPIC_H__
#define __INTENTS_TOPICS_MOTION_PLANNING_DEBUG_TOPIC_H__

#include <array>
#include <cstdint>
#include <tuple>
#include "data/defs/waypoint.h"
#include "intents/topics/common.h"

namespace cooboc {
namespace intent {

struct MotionPlanningDebugTopic {
    static constexpr std::size_t kWaypointNumber {500U};

    std::size_t numberOfWaypoints {0U};
    data::Waypoint waypoints[kWaypointNumber];

    std::array<std::tuple<float, float>, kTrajectoryPassingPointCapacity>
      longitudinalCurvatureProfile {};
};

}    // namespace intent
}    // namespace cooboc

#endif
