#ifndef __INTENTS_MOTION_PLANNING_INTENT_MOTION_PLANNING_INTENT_H__
#define __INTENTS_MOTION_PLANNING_INTENT_MOTION_PLANNING_INTENT_H__

#include <tuple>
#include "data/defs/pose2d.h"
#include "data/defs/static_vector.h"
#include "intents/intent_base.h"
#include "intents/topics/common.h"
#include "intents/topics/route_topic.h"
#include "intents/topics/trajectory_topic.h"
#include "utils/algo/pid.h"

namespace cooboc {
namespace intent {

namespace detail {

struct ReferencePose {
    float s {0.0};              // the s on the reference path
    float y {0.0};              // ego lateral based on reference path
    float orientation {0.0};    // the angle of reference path
};

ReferencePose calculatePositionInFrenet(const data::Pose2D &odometry, const RouteTopic &route);
float calculateDistanceFromPointToSegment(const data::Position2D &point,
                                          const data::Position2D &segmentStart,
                                          const data::Position2D &segmentEnd,
                                          const bool isStartClosed = true,
                                          const bool isEndClosed   = true);

using CurvatureProfile =
  data::StaticVector<std::tuple<float, float>, kTrajectoryPassingPointCapacity>;
void calculateCurvatureProfile(const data::PassingPoint *passingPoint,
                               const std::size_t &passingPointSize,
                               CurvatureProfile &curvatureProfile);


}    // namespace detail

class MotionPlanningIntent : public IntentBase {
  public:
    MotionPlanningIntent();
    virtual ~MotionPlanningIntent();
    virtual void setup() override;
    virtual void tick() override;

  private:
    void planEgoMotion(const data::Pose2D &inintOdometry,
                       const data::PolarVector2D &initVelocity,
                       const data::PolarVector2D &initAcceleration);


    algo::PID<float> lateralPid_ {};
    detail::CurvatureProfile curvatureProfile_;
};

}    // namespace intent
}    // namespace cooboc

#endif
