#ifndef __INTENTS_TRAJECTORY_INTENT_TRAJECTORY_INTENT_H__
#define __INTENTS_TRAJECTORY_INTENT_TRAJECTORY_INTENT_H__


#include <array>
#include <optional>
#include <vector>
#include "data/defs/passing_point.h"
#include "data/defs/static_vector.h"
#include "intents/intent_base.h"
#include "intents/topics/topics.h"
#include "intents/trajectory_intent/trajectory/trajectory.h"

namespace cooboc {
namespace intent {

// TrajectoryIntent take the Route from RouteIntent and make a trajectory that vehicle can follow
class TrajectoryIntent : public IntentBase {
  public:
    // TrajectoryIntent take the Route from RouteIntent and make a trajectory that vehicle can
    // follow
    TrajectoryIntent();
    virtual ~TrajectoryIntent();
    virtual void setup() override;
    virtual void tick() override;

  private:
    trajectory::PassingPointList passingPointList_ {};
    TrajectoryId trajectoryId_ {0U};

    void outputTopic();
    TrajectoryId makeNewTrajectoryId();
};


}    // namespace intent
}    // namespace cooboc

#endif
