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
    algo::PID<float> lateralPid_ {};
    motion_planning::CurvatureProfile curvatureProfile_;
    motion_planning::MotionProfile motionProfile_;
    data::Pose2D poseInFrenet_ {};

    void planLongitudinal(const float initS, const float initSpeed);
    void normalizeS(std::size_t &trajectoryIdx, float &s);
    std::tuple<data::Position2D, bool> mapSToPosition(std::size_t &trajectoryIdx, const float s);

    struct LongitudinalPlanningPoint {
        std::size_t trajectoryIdx {0U};
        float segmentS {0.0F};
        float speed {0.0F};
        data::Position2D waypoint {};

        // debug
        data::Vector2D motionVelocity {};
    };


    std::array<LongitudinalPlanningPoint, kPlanningSize> longitudinalPlanning_ {};
};

}    // namespace intent
}    // namespace cooboc

#endif
