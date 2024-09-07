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
            vehicleRequestTopic.wheelControlPlanning[i].speed[j] = 0.0F;
        }
    }
}
void VehicleRequestIntent::tick() {
    // TODO: mock a speed

    // const data::PolarVector2D fakeVelocity = {utils::math::PI / 16.0F, 0.3F};
    // const float rotation             = 0.01F;

    const data::PolarVector2D fakeVelocity = {0.0F, 0.0F};
    const float rotation                   = 0.0F;

    data::Vector2D velocityVec = motionPlanningTopic.waypoints[0U].velocity;


    vehicleRequestTopic.wheelControlPlanning[0U].speed[0U] =
      velocityVec.x + velocityVec.y + rotation;
    vehicleRequestTopic.wheelControlPlanning[1U].speed[0U] =
      velocityVec.x - velocityVec.y + rotation;
    vehicleRequestTopic.wheelControlPlanning[2U].speed[0U] =
      velocityVec.x + velocityVec.y - rotation;
    vehicleRequestTopic.wheelControlPlanning[3U].speed[0U] =
      velocityVec.x - velocityVec.y - rotation;

    // do nothing
}


}    // namespace intent
}    // namespace cooboc