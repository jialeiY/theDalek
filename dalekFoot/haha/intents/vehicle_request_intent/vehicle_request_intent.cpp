#include "intents/vehicle_request_intent/vehicle_request_intent.h"
#include "intents/topics/topics.h"

namespace cooboc {
namespace intent {
VehicleRequestIntent::VehicleRequestIntent() {}
VehicleRequestIntent::~VehicleRequestIntent() {}
void VehicleRequestIntent::setup() { vehicleRequestTopic.velocity = {0.0F, 1.0F}; }
void VehicleRequestIntent::tick() {
    // do nothing
}


}    // namespace intent
}    // namespace cooboc