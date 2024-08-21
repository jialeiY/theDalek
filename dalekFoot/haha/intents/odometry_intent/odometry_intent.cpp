#include "intents/odometry_intent/odometry_intent.h"
#include <cmath>
#include <cstdint>
#include <random>
#include "data/defs/polar_vector2d.h"
#include "data/defs/vector2d.h"
#include "intents/topics/topics.h"
#include "utils/math.h"
#include "utils/time.h"

namespace cooboc {
namespace intent {
OdometryIntent::OdometryIntent() :
    isInitialized_ {false},
    randomDev_ {},
    randomGen_ {randomDev_()},
    randomDistribution_ {0.0F, 0.02F} {}

OdometryIntent::~OdometryIntent() {}

void OdometryIntent::setup() {
    odometryTopic.timestamp        = 0U;
    odometryTopic.pose.position.x  = 0.0F;
    odometryTopic.pose.position.y  = 0.0F;
    odometryTopic.pose.orientation = 0.0F;
}


void OdometryIntent::tick() {
    // odometryTopic.timestamp        = utils::time::nanoseconds();
    // odometryTopic.pose.position.x  = randomDistribution_(randomGen_);
    // odometryTopic.pose.position.y  = randomDistribution_(randomGen_);
    // odometryTopic.pose.orientation = randomDistribution_(randomGen_) * 5.4F;


    // std::uint64_t fromm = utils::time::milliseconds();
    // fromm %= 5000;

    // odometryTopic.pose.orientation = utils::math::lerp(
    //   static_cast<float>(fromm), 0.0F, 5000.0F, 0.0F, 2 * utils::math::PI);


    constexpr float kAxelLongitudinal {0.25F};
    constexpr float kAxelLateral {0.20F};

    if (isInitialized_) {
        int64_t encoderDiff[4];
        float dist[4];
        for (std::size_t i {0U}; i < 4U; ++i) {
            encoderDiff[i] = vehicleResponseTopic.response.wheelStatus[i].encoder - encoder_[i];
            // TODO: make it a parameter
            dist[i]     = (static_cast<float>(encoderDiff[i]) / 4096.0) * (utils::math::PI * 0.06);
            encoder_[i] = vehicleResponseTopic.response.wheelStatus[i].encoder;
        }
        float diffx = dist[0] + dist[1] + dist[2] + dist[3];
        float diffy = dist[0] - dist[1] + dist[2] - dist[3];
        float diffr = dist[0] + dist[1] - dist[2] - dist[3];
        std::printf("encoder: %ld %ld %ld %ld\r\n",
                    encoderDiff[0],
                    encoderDiff[1],
                    encoderDiff[2],
                    encoderDiff[3]);

        float angularDiff =
          diffr * (2.0 * utils::math::PI /
                   std::sqrt(kAxelLongitudinal * kAxelLongitudinal + kAxelLateral * kAxelLateral));

        const data::Vector2D posDiffVec {diffx, diffy};
        data::PolarVector2D posDiffPolar {utils::math::to<data::PolarVector2D>(posDiffVec)};

        // rotate first
        posDiffPolar.orientation += odometryTopic.pose.orientation;

        odometryTopic.pose.position = odometryTopic.pose.position + posDiffPolar;
        odometryTopic.pose.orientation += angularDiff;


        // odometryTopic.pose.position.x += diffx;
        // odometryTopic.pose.position.y += diffy;


    } else {
        for (std::size_t i {0U}; i < 4U; ++i) {
            encoder_[i] = vehicleResponseTopic.response.wheelStatus[i].encoder;
        }
        isInitialized_ = true;
    }
}
}    // namespace intent
}    // namespace cooboc