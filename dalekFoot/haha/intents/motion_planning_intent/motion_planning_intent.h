#ifndef __INTENTS_MOTION_PLANNING_INTENT_MOTION_PLANNING_INTENT_H__
#define __INTENTS_MOTION_PLANNING_INTENT_MOTION_PLANNING_INTENT_H__

#include <array>
#include <tuple>
#include "data/defs/pose2d.h"
#include "data/defs/static_vector.h"
#include "intents/intent_base.h"
#include "intents/motion_planning_intent/components/profile.h"
#include "intents/topics/common.h"
#include "intents/topics/route_topic.h"
#include "intents/topics/trajectory_topic.h"
#include "utils/algo/pid.h"

namespace cooboc {
namespace intent {

// namespace detail {

// struct ReferencePose {
//     float s {0.0};              // the s on the reference path
//     float y {0.0};              // ego lateral based on reference path
//     float orientation {0.0};    // the angle of reference path
// };

// ReferencePose calculatePositionInFrenet(const data::Pose2D &odometry, const RouteTopic &route);
// float calculateDistanceFromPointToSegment(const data::Position2D &point,
//                                           const data::Position2D &segmentStart,
//                                           const data::Position2D &segmentEnd,
//                                           const bool isStartClosed = true,
//                                           const bool isEndClosed   = true);


// }    // namespace detail


class MotionPlanningIntent : public IntentBase {
  public:
    MotionPlanningIntent();
    virtual ~MotionPlanningIntent();
    virtual void setup() override;
    virtual void tick() override;

  private:
    void planLongitudinal(const float initSpeed);


    void planEgoMotion(const data::Pose2D &inintOdometry,
                       const data::PolarVector2D &initVelocity,
                       const data::PolarVector2D &initAcceleration);


    algo::PID<float> lateralPid_ {};
    motion_planning::CurvatureProfile curvatureProfile_;
    motion_planning::MotionProfile motionProfile_;
    data::Pose2D poseInFrenet_ {};


    /**
     * tuple : < s - velocity >
     */
    using LongitudinalWaypoint = std::tuple<float, float>;
    std::array<LongitudinalWaypoint, kPlanningSize> longitudinalPlanning_;
};

}    // namespace intent
}    // namespace cooboc

#endif
