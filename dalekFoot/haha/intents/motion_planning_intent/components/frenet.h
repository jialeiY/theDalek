#ifndef __INTENTS_MOTION_PLANNING_INTENT_COMPONENTS_FRENET_H__
#define __INTENTS_MOTION_PLANNING_INTENT_COMPONENTS_FRENET_H__

#include <cstdint>
#include "data/defs/passing_point.h"
#include "data/defs/pose2d.h"


namespace cooboc {
namespace intent {
namespace motion_planning {
namespace detail {
float calculateDistanceFromPointToSegment(const data::Position2D &point,
                                          const data::Position2D &segmentStart,
                                          const data::Position2D &segmentEnd,
                                          const bool isStartClosed,
                                          const bool isEndClosed);
}    // namespace detail

std::size_t calculatePoseInFrenet(const data::Pose2D &poseInWorld,
                                  const data::PassingPoint *passingPoint,
                                  const std::size_t &passingPointSize,
                                  data::Pose2D &poseInFrenet);


}    // namespace motion_planning
}    // namespace intent
}    // namespace cooboc


#endif
