#include "data/codec/motion_planning_topic_codec.h"
#include <cstdint>
#include "data/codec/waypoint_codec.h"
#include "gen/data/proto/motion_planning_topic.pb.h"
#include "gen/data/proto/waypoint.pb.h"
#include "intents/topics/common.h"
#include "intents/topics/motion_planning_topic.h"

namespace cooboc {
namespace data {

proto::MotionPlanningTopic convert(const intent::MotionPlanningTopic &in) {
    proto::MotionPlanningTopic out;
    for (std::size_t i {0U}; i < intent::kPlanningSize; ++i) {
        proto::Waypoint *waypoint = out.add_waypoints();

        *waypoint = convert(in.waypoints[i]);
    }

    return out;
}

}    // namespace data
}    // namespace cooboc