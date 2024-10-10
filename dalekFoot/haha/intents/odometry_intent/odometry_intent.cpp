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
    randomDistribution_ {0.0F, 0.02F} {
    for (std::size_t i {0U}; i < 4U; ++i) { encoderOdometry_[i] = 0; }
}

OdometryIntent::~OdometryIntent() {}

void OdometryIntent::setup() {
    shared::odometryTopic.timestamp        = 0U;
    shared::odometryTopic.pose.position.x  = 0.0F;
    shared::odometryTopic.pose.position.y  = 0.0F;
    shared::odometryTopic.pose.orientation = 0.0F;
}


void OdometryIntent::tick() {
    if (!shared::vehicleResponseTopic.isValid) {
        // TODO: update odometry using history information
        return;
    }
    // TODO: update odometry use history information
    // odometryTopic.timestamp        = utils::time::nanoseconds();
    // odometryTopic.pose.position.x  = randomDistribution_(randomGen_);
    // odometryTopic.pose.position.y  = randomDistribution_(randomGen_);
    // odometryTopic.pose.orientation = randomDistribution_(randomGen_) * 5.4F;


    // std::uint64_t fromm = utils::time::milliseconds();
    // fromm %= 5000;

    // odometryTopic.pose.orientation = utils::math::lerp(
    //   static_cast<float>(fromm), 0.0F, 5000.0F, 0.0F, 2 * utils::math::PI);

    // TODO: make this variable to parameter
    constexpr float kAxelLongitudinal {0.25F};
    constexpr float kAxelLateral {0.20F};

    if (isInitialized_) {
        std::int64_t encoderDiff[4];
        for (std::size_t i {0U}; i < 4U; ++i) {
            encoderDiff[i] = shared::vehicleResponseTopic.encoderOdometry[i] - encoderOdometry_[i];

            // Update status
            encoderOdometry_[i] = shared::vehicleResponseTopic.encoderOdometry[i];
        }
        constexpr float kEncoderToMetric = utils::math::PI * 0.06F / 4096.0F;
        const float diffX =
          static_cast<float>(encoderDiff[0] + encoderDiff[1] + encoderDiff[2] + encoderDiff[3]) *
          kEncoderToMetric / 4.0F;
        const float diffY =
          static_cast<float>(encoderDiff[0] - encoderDiff[1] + encoderDiff[2] - encoderDiff[3]) *
          kEncoderToMetric / 4.0F;
        const float diffR =
          static_cast<float>(encoderDiff[0] + encoderDiff[1] - encoderDiff[2] - encoderDiff[3]) *
          kEncoderToMetric;
        const float angularDiff =
          diffR * (2.0 * utils::math::PI /
                   std::sqrt(kAxelLongitudinal * kAxelLongitudinal + kAxelLateral * kAxelLateral));
        const data::Vector2D posDiffVec {diffX, diffY};
        data::PolarVector2D posDiffPolar {utils::math::to<data::PolarVector2D>(posDiffVec)};

        // Rotate the vehicle
        posDiffPolar.orientation += shared::odometryTopic.pose.orientation;
        // Translate the vehicle
        shared::odometryTopic.pose.position = shared::odometryTopic.pose.position + posDiffPolar;
        shared::odometryTopic.pose.orientation += angularDiff;
    } else {
        for (std::size_t i {0U}; i < 4U; ++i) {
            encoderOdometry_[i] = shared::vehicleResponseTopic.encoderOdometry[i];
        }
        isInitialized_ = true;
    }
}
}    // namespace intent
}    // namespace cooboc