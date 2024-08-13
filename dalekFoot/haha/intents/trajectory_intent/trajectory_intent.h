#ifndef __INTENTS_TRAJECTORY_INTENT_TRAJECTORY_INTENT_H__
#define __INTENTS_TRAJECTORY_INTENT_TRAJECTORY_INTENT_H__


#include "intents/intent_base.h"

namespace cooboc {
namespace intent {

namespace detail {
float calculateApproximateRouteLength();
}


// TrajectoryIntent take the Route from RouteIntent and make a trajectory that vehicle can follow
class TrajectoryIntent : public IntentBase {
  public:
    // TrajectoryIntent take the Route from RouteIntent and make a trajectory that vehicle can
    // follow
    TrajectoryIntent();
    virtual ~TrajectoryIntent();
    virtual void setup() override;
    virtual void tick() override;
};


}    // namespace intent
}    // namespace cooboc

#endif
