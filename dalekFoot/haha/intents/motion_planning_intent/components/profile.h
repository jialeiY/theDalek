#ifndef __INTENTS_MOTION_PLANNING_INTENT_COMPONENTS_PROFILE_H__
#define __INTENTS_MOTION_PLANNING_INTENT_COMPONENTS_PROFILE_H__


#include <tuple>
#include "data/defs/passing_point.h"
#include "data/defs/static_vector.h"
#include "intents/topics/common.h"

namespace cooboc {
namespace intent {
namespace motion_planning {


// tuple = <the length on the trajectory, curvature changing between previous and next segment>
using CurvatureProfile =
  data::StaticVector<std::tuple<float, float>, kReferencePathPassingPointCapacity>;

// tuple = <the maximum velocity, the maximum acceleration>
using MotionProfile =
  data::StaticVector<std::tuple<float, float>, kReferencePathPassingPointCapacity>;

/**
 * Calculate the curvature changing on each passing point on the trajectory. The changing rate on
 * the first point and the last point is 0.
 * @param passingPoint [in]: The passing point list in trajectory
 * @param passingPointSize [in]: The size of passing point list
 * @param curvatureProfile [out]: The curvature changing rate on each passing point.
 * @return void
 */
void calculateCurvatureProfile(const data::PassingPoint *passingPoint,
                               const std::size_t &passingPointSize,
                               CurvatureProfile &curvatureProfile);


void calculateMotionProfile(const CurvatureProfile &curvatureProfile,
                            const float maximumAcceleration,
                            const float maximumVelocity,
                            MotionProfile &motionProfile);

}    // namespace motion_planning
}    // namespace intent
}    // namespace cooboc

#endif
