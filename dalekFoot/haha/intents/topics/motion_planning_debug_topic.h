#ifndef __INTENTS_TOPICS_MOTION_PLANNING_DEBUG_TOPIC_H__
#define __INTENTS_TOPICS_MOTION_PLANNING_DEBUG_TOPIC_H__

#include <array>
#include <cstdint>
#include <tuple>
#include "data/defs/pose2d.h"
#include "data/defs/waypoint.h"
#include "intents/topics/common.h"
#include "intents/topics/reference_path_topic.h"

namespace cooboc {
namespace intent {

struct MotionPlanningDebugTopic {
    static constexpr std::size_t kWaypointNumber {500U};

    std::size_t numberOfWaypoints {0U};
    data::Waypoint waypoints[kWaypointNumber];

    std::array<std::tuple<float, float>, intent::ReferencePathTopic::kReferencePathPointsCapacity>
      longitudinalCurvatureProfile {};

    std::array<std::tuple<float, float>, intent::ReferencePathTopic::kReferencePathPointsCapacity>
      longitudinalMotionProfile {};


    std::int64_t trajectoryPointIdx {-1};

    data::Pose2D poseInFrenet {};
    float distanceToTrajectory {0.0F};
};

}    // namespace intent
}    // namespace cooboc

#endif
