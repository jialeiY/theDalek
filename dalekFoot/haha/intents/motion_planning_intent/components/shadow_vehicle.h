#ifndef __INTENTS_MOTION_PLANNING_INTENT_COMPONENTS_SHADOW_VEHICLE_H__
#define __INTENTS_MOTION_PLANNING_INTENT_COMPONENTS_SHADOW_VEHICLE_H__


#include "data/defs/motion_state.h"
#include "data/defs/pose2d.h"
#include "data/defs/vehicle_state.h"


namespace cooboc {
namespace intent {
namespace motion_planning {
class ShadowVehicle {
  public:
    ShadowVehicle()          = default;
    virtual ~ShadowVehicle() = default;

    inline void setValid(bool valid) { isValid_ = valid; }
    inline bool isValid() const { return isValid_; }
    inline void setPose(const data::Pose2D &pose) { vehicleState_.pose = pose; }
    inline void setMotionState(const data::MotionState &motionState) {
        vehicleState_.motionState = motionState;
    }

    inline data::VehicleState getVehicleState() const { return vehicleState_; }

  private:
    bool isValid_ {false};
    data::VehicleState vehicleState_ {};
};

}    // namespace motion_planning
}    // namespace intent
}    // namespace cooboc

#endif
