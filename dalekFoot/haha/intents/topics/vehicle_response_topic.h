#ifndef __INTENT_TOPICS_VEHICLE_RESPONSE_TOPIC_H__
#define __INTENT_TOPICS_VEHICLE_RESPONSE_TOPIC_H__

#include "data/defs/vehicle_response.h"

namespace cooboc {
namespace intent {

struct VehicleResponseTopic {
    bool isValid {false};
    std::uint32_t tickCount {0U};
    std::int32_t encoderOdometry[4U] {};
    std::int32_t intervalOdometry[4U] {};
};

}    // namespace intent

}    // namespace cooboc


#endif
