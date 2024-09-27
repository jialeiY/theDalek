#include "intents/vehicle_request_intent/vehicle_request_intent.h"
#include <cstdint>
#include <cstring>
#include "data/defs/polar_vector2d.h"
#include "data/defs/vector2d.h"
#include "data/gh_protocol.h"
#include "intents/topics/topics.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {
VehicleRequestIntent::VehicleRequestIntent() {}
VehicleRequestIntent::~VehicleRequestIntent() {}
void VehicleRequestIntent::setup() {
    static_assert(cooboc::comm::HGPacket::kPlanningSize == cooboc::intent::kControlSize);

    for (std::size_t i {0U}; i < 4U; ++i) {
        for (std::size_t j {0U}; j < 10U; ++j) {
            vehicleRequestTopic.wheelControlPlanning[i].encoderSpeed[j] = 0.0F;
        }
    }
    std::memset(vehicleRequestTopic.hgPacketBuffer, 0, HG_PACKET_SIZE);
}
void VehicleRequestIntent::tick() {
    // TODO: mock a speed

    // const data::PolarVector2D fakeVelocity = {utils::math::PI / 16.0F, 0.3F};
    // const float rotation             = 0.01F;

    const data::PolarVector2D fakeVelocity = {0.0F, 0.0F};
    const float rotation                   = 0.0F;

    comm::HGPacket packet {};
    constexpr float kMetricToEncoder = 4096.0F / (utils::math::PI * 0.06F);
    for (std::size_t i {0U}; i < kControlSize; ++i) {
        const data::Vector2D &velocityVec = motionPlanningTopic.waypoints[i].velocity;
        vehicleRequestTopic.wheelControlPlanning[0U].encoderSpeed[i] =
          (velocityVec.x + velocityVec.y + rotation) * kMetricToEncoder;
        vehicleRequestTopic.wheelControlPlanning[1U].encoderSpeed[i] =
          (velocityVec.x - velocityVec.y + rotation) * kMetricToEncoder;
        vehicleRequestTopic.wheelControlPlanning[2U].encoderSpeed[i] =
          (velocityVec.x + velocityVec.y - rotation) * kMetricToEncoder;
        vehicleRequestTopic.wheelControlPlanning[3U].encoderSpeed[i] =
          (velocityVec.x - velocityVec.y - rotation) * kMetricToEncoder;


        packet.wheelEncoderPlanning[0U][i] =
          vehicleRequestTopic.wheelControlPlanning[0U].encoderSpeed[i];
        packet.wheelEncoderPlanning[1U][i] =
          vehicleRequestTopic.wheelControlPlanning[1U].encoderSpeed[i];
        packet.wheelEncoderPlanning[2U][i] =
          vehicleRequestTopic.wheelControlPlanning[2U].encoderSpeed[i];
        packet.wheelEncoderPlanning[3U][i] =
          vehicleRequestTopic.wheelControlPlanning[3U].encoderSpeed[i];
    }

    std::uint32_t crc = utils::math::calculateCrc(packet);
    packet.crc        = crc;

    // write to buffer

    std::memcpy(vehicleRequestTopic.hgPacketBuffer,
                reinterpret_cast<std::uint8_t *>(&packet),
                HG_PACKET_SIZE);
}


}    // namespace intent
}    // namespace cooboc