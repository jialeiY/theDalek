#ifndef __INTENTS_MOTION_PLANNING_INTENT_MOTION_PLANNING_INTENT_H__
#define __INTENTS_MOTION_PLANNING_INTENT_MOTION_PLANNING_INTENT_H__

#include "data/defs/pose2d.h"
#include "intents/intent_base.h"
#include "intents/topics/route_topic.h"

namespace cooboc {
namespace intent {

namespace detail {
data::Position2D calculatePositionInFrene(const data::Pose2D &odometry,
                                          const RouteTopic &route);
float calculateDistanceFromPointToSegment(const data::Position2D &point,
                                          const data::Position2D &segmentStart,
                                          const data::Position2D &segmentEnd,
                                          const bool isStartClosed = true,
                                          const bool isEndClosed   = true);
}    // namespace detail

class MotionPlanningIntent : public IntentBase {
  public:
    MotionPlanningIntent();
    virtual ~MotionPlanningIntent();
    virtual void setup() override;
    virtual void tick() override;

  private:
};

}    // namespace intent
}    // namespace cooboc

#endif
