#ifndef __INTENTS_TOPICS_VEHICLE_REQUEST_TOPIC_H__
#define __INTENTS_TOPICS_VEHICLE_REQUEST_TOPIC_H__

#include "data/defs/polar_vector2d.h"
#include "data/defs/vector2d.h"


namespace cooboc {
namespace intent {

struct VehicleRequestTopic {
    data::PolarVector2D velocity {};
};
}    // namespace intent
}    // namespace cooboc

#endif
