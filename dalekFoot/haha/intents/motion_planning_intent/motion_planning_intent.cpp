#include "intents/motion_planning_intent/motion_planning_intent.h"
#include <cstdio>
#include <iostream>
#include <limits>
#include "data/defs/pose2d.h"
#include "intents/topics/topics.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {

namespace detail {
data::Position2D calculatePositionInFrene(const data::Pose2D &odometry, const RouteTopic &route) {
    std::cout << "odo: " << odometry.position.x << ", " << odometry.position.y << std::endl;
    // TODO, assume route always has data now

    // Find the segment
    std::size_t closestSegmentId {0U};
    float closestDistance {std::numeric_limits<float>::max()};

    const std::size_t segmentNumber = route.polylineLength - 1U;
    for (std::size_t i {0U}; i < segmentNumber; ++i) {
        bool firstNeedOpen = i != 0U;    // only first one open
        float dist         = std::fabs(calculateDistanceFromPointToSegment(
          odometry.position, route.polyline[i], route.polyline[i + 1U], firstNeedOpen, true));
        if (dist < closestDistance) {
            closestSegmentId = i;
            closestDistance  = dist;
        }
    }

    std::cout << "closest id: " << closestSegmentId << " dist = " << closestDistance << std::endl;


    float s = 0.0F;
    // Calculate all s before current segment
    for (std::size_t i {0U}; (i + 1U) < closestSegmentId; ++i) {
        s += route.polyline[i].distance(route.polyline[i + 1U]);
    }

    // Calculate s on current segment
    if (!utils::math::equals(route.polyline[closestSegmentId],
                             route.polyline[closestSegmentId + 1U])) {
        const data::Position2D veca =
          route.polyline[closestSegmentId + 1U] - route.polyline[closestSegmentId];
        const data::Position2D vecb = odometry.position - route.polyline[closestSegmentId];
        s += veca.dot(vecb) / veca.abs();
    }

    data::Position2D ret {s,
                          calculateDistanceFromPointToSegment(odometry.position,
                                                              route.polyline[closestSegmentId],
                                                              route.polyline[closestSegmentId + 1U],
                                                              false,
                                                              false)};
    return ret;
}

float calculateDistanceFromPointToSegment(const data::Position2D &point,
                                          const data::Position2D &segmentStart,
                                          const data::Position2D &segmentEnd,
                                          const bool isStartClosed,
                                          const bool isEndClosed) {
    // Is start equals to end
    if (utils::math::equals(segmentStart, segmentEnd)) {
        return point.distance(segmentStart);
    }

    // is on the start point?
    if (utils::math::equals(point.x, segmentStart.x) &&
        utils::math::equals(point.y, segmentStart.y)) {
        return 0.0F;
    }

    // is on the end point?
    if ((utils::math::equals(point.x, segmentEnd.x)) &&
        (utils::math::equals(point.y, segmentEnd.y))) {
        return 0.0F;
    }

    // Point out side of start
    if (isStartClosed) {
        if ((point - segmentStart).dot(segmentEnd - segmentStart) < 0.0F) {
            return point.distance(segmentStart);
        }
    }

    // Point out side of end
    if (isEndClosed) {
        if ((point - segmentEnd).dot(segmentStart - segmentEnd) < 0.0F) {
            return point.distance(segmentEnd);
        }
    }

    // // the representation of line is Ax + By + C = 0;
    // // d = |Ax + Ｂy + C| / sqrt(A^2 + B^2)
    // const float A = (segmentEnd.y - segmentStart.y);
    // const float B = (segmentStart.x - segmentEnd.x);
    // const float C =
    //   (segmentEnd.x * segmentStart.y) - (segmentStart.x * segmentEnd.y);
    // const float dist2line = std::fabs((A * point.x) + (B * point.y) + C) /
    //                         std::sqrt((A * A) + (B * B));
    const float dist2line =
      ((segmentEnd - segmentStart).cross(point - segmentStart)) / segmentStart.distance(segmentEnd);
    return dist2line;
}

}    // namespace detail


MotionPlanningIntent::MotionPlanningIntent() {
    motionPlanningDebugTopic.numberOfWaypoints = 0U;
    for (std::size_t i {0U}; i < MotionPlanningDebugTopic::kWaypointNumber; ++i) {
        motionPlanningDebugTopic.waypoints[i].pose      = {data::Position2D {0.0F, 0.0F}, 0.0F};
        motionPlanningDebugTopic.waypoints[i].timepoint = 0U;
    }
}
MotionPlanningIntent::~MotionPlanningIntent() {}
void MotionPlanningIntent::setup() {}


void MotionPlanningIntent::tick() {
    std::cout << std::endl << std::endl << "=======" << std::endl;
    // 0. Setup the input data
    // Odometry
    const data::Pose2D &odometry = odometryTopic.pose;
    // Reference path
    const RouteTopic &route = routeTopic;

    // 1. Odometry to frenet
    const data::Position2D initPosition = detail::calculatePositionInFrene(odometry, route);
    // Generate trajectory of 10 waypoints

    motionPlanningDebugTopic.numberOfWaypoints = 10U;
    for (std::size_t i {0U}; i < 10U; ++i) {
        data::Waypoint &waypoint {motionPlanningDebugTopic.waypoints[i]};
        waypoint.timepoint        = odometryTopic.timestamp + (10U * 1000U * i);
        waypoint.pose.orientation = odometry.orientation;
        waypoint.pose.position    = initPosition;
    }
}


}    // namespace intent
}    // namespace cooboc