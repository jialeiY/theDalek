#ifndef __INTENT_TOPICS_VEHICLE_RESPONSE_TOPIC_H__
#define __INTENT_TOPICS_VEHICLE_RESPONSE_TOPIC_H__

#include "data/defs/vehicle_response.h"

namespace cooboc {
namespace intent {

struct VehicleResponseTopic {
    bool isValid {false};
    std::int32_t encoderOdometry[4U];
    float encoderSpeed[4U];
};

}    // namespace intent

}    // namespace cooboc


#endif
