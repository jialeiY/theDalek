#ifndef __DATA_DEFS_VEHICLE_STATE_H__
#define __DATA_DEFS_VEHICLE_STATE_H__

#include "data/defs/motion_state.h"
#include "data/defs/pose2d.h"


namespace cooboc {
namespace data {
struct VehicleState {
    data::Pose2D pose;                // localization
    data::MotionState motionState;    // motion state
};

}    // namespace data
}    // namespace cooboc

#endif
