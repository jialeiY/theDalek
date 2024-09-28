#ifndef __INTENTS_MOTION_PLANNING_INTENT_COMPONENTS_SHADOW_VEHICLE_H__
#define __INTENTS_MOTION_PLANNING_INTENT_COMPONENTS_SHADOW_VEHICLE_H__


#include "data/defs/motion_state.h"
#include "data/defs/pose2d.h"


namespace cooboc {
namespace intent {
namespace motion_planning {
class ShadowVehicle {
  public:
    ShadowVehicle()          = default;
    virtual ~ShadowVehicle() = default;
    inline void setPose(const data::Pose2D &pose) { pose_ = pose; }

  private:
    bool isValid {false};
    data::Pose2D pose_ {};
    data::MotionState state_ {};
};

}    // namespace motion_planning
}    // namespace intent
}    // namespace cooboc

#endif
