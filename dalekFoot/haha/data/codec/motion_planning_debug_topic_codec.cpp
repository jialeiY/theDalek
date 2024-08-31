#include "data/codec/motion_planning_debug_topic_codec.h"
#include <algorithm>
#include <cstdint>
#include "data/codec/waypoint_codec.h"
#include "gen/data/proto/motion_planning_debug_topic.pb.h"
#include "gen/data/proto/waypoint.pb.h"
#include "intents/topics/motion_planning_debug_topic.h"

namespace cooboc {
namespace data {

proto::MotionPlanningDebugTopic convert(const intent::MotionPlanningDebugTopic &in) {
    proto::MotionPlanningDebugTopic out;
    out.set_numberofwaypoints(in.numberOfWaypoints);
    for (std::size_t i {0U}; i < intent::MotionPlanningDebugTopic::kWaypointNumber; ++i) {
        proto::Waypoint *waypoint = out.add_waypoints();
        *waypoint                 = convert(in.waypoints[i]);
    }

    // To flatten the data for visualization only
    const std::size_t waypointLength {
      std::min(intent::MotionPlanningDebugTopic::kWaypointNumber, in.numberOfWaypoints)};
    for (std::size_t i {0U}; i < waypointLength; ++i) {
        out.add_waypoint_timepoint(in.waypoints[i].timepoint);
        out.add_waypoint_position_x(in.waypoints[i].pose.position.x);
        out.add_waypoint_position_y(in.waypoints[i].pose.position.y);

        out.add_waypoint_velocity_y(in.waypoints[i].velocityY);            // Debug
        out.add_waypoint_acceleration_y(in.waypoints[i].accelerationY);    // Debug
    }

    for (const auto &lcp : in.longitudinalCurvatureProfile) {
        proto::LongitudinalCurvatureProfile *longitudinalCurvatureProfile =
          out.add_longitudinalcurvatureprofile();

        longitudinalCurvatureProfile->set_s(std::get<0U>(lcp));
        longitudinalCurvatureProfile->set_curvature(std::get<1U>(lcp));
    }

    for (const auto &mcp : in.longitudinalMotionProfile) {
        proto::LongitudinalMotionProfile *longitudinalMotionProfile =
          out.add_longitudinalmotionprofile();
        longitudinalMotionProfile->set_maximumvelocity(std::get<0U>(mcp));
        longitudinalMotionProfile->set_maximumacceleration(std::get<1U>(mcp));
    }
    return out;
}

}    // namespace data
}    // namespace cooboc