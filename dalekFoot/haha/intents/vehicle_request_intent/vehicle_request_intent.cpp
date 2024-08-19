#include "intents/vehicle_request_intent/vehicle_request_intent.h"
#include <cstdint>
#include "data/defs/polar_vector2d.h"
#include "data/defs/vector2d.h"
#include "intents/topics/topics.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {
VehicleRequestIntent::VehicleRequestIntent() {}
VehicleRequestIntent::~VehicleRequestIntent() {}
void VehicleRequestIntent::setup() {
    for (std::size_t i {0U}; i < 4U; ++i) {
        for (std::size_t j {0U}; j < 10U; ++j) {
            vehicleRequestTopic.wheelSpeedPlanning[i][j] = 0.0F;
        }
    }
}
void VehicleRequestIntent::tick() {
    // TODO: mock a speed

    const data::PolarVector2D fakeVelocity = {utils::math::PI / 16.0F, 0.3F};

    const data::Vector2D velocityVec = utils::math::to<data::Vector2D>(fakeVelocity);
    const float rotation             = 0.5F;

    vehicleRequestTopic.wheelSpeedPlanning[0U][0U] = velocityVec.x + velocityVec.y + rotation;
    vehicleRequestTopic.wheelSpeedPlanning[1U][0U] = velocityVec.x - velocityVec.y + rotation;
    vehicleRequestTopic.wheelSpeedPlanning[2U][0U] = velocityVec.x + velocityVec.y - rotation;
    vehicleRequestTopic.wheelSpeedPlanning[3U][0U] = velocityVec.x - velocityVec.y - rotation;

    // do nothing
}


}    // namespace intent
}    // namespace cooboc