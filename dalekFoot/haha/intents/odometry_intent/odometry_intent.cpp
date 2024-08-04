#include "intents/odometry_intent/odometry_intent.h"
#include <random>
#include "intents/topics/topics.h"
#include "utils/math.h"
#include "utils/time.h"

namespace cooboc {
namespace intent {
OdometryIntent::OdometryIntent() :
    randomDev_ {},
    randomGen_ {randomDev_()},
    randomDistribution_ {0.0F, 0.02F} {}

OdometryIntent::~OdometryIntent() {}

void OdometryIntent::setup() {
    odometryTopic.timestamp        = 0U;
    odometryTopic.pose.position.x  = 0.0F;
    odometryTopic.pose.position.y  = 0.0F;
    odometryTopic.pose.orientation = 0.0F;

    egoStateTopic.velocity            = {0.0F, 0.0F};
    egoStateTopic.acceleration        = {0.0F, 0.0F};
    egoStateTopic.angularVelocity     = 0.0F;
    egoStateTopic.angularAcceleration = 0.0F;
}


void OdometryIntent::tick() {
    odometryTopic.timestamp        = utils::time::nanoseconds();
    odometryTopic.pose.position.x  = randomDistribution_(randomGen_);
    odometryTopic.pose.position.y  = randomDistribution_(randomGen_);
    odometryTopic.pose.orientation = randomDistribution_(randomGen_) * 5.4F;

    egoStateTopic.velocity.orientation = randomDistribution_(randomGen_) * 3.9F;
    egoStateTopic.velocity.value       = randomDistribution_(randomGen_) * 3.0 + 0.5;

    egoStateTopic.acceleration.orientation = randomDistribution_(randomGen_) * 39.4F;
    egoStateTopic.acceleration.value       = randomDistribution_(randomGen_) * 4.7;


    // std::uint64_t fromm = utils::time::milliseconds();
    // fromm %= 5000;

    // odometryTopic.pose.orientation = utils::math::lerp(
    //   static_cast<float>(fromm), 0.0F, 5000.0F, 0.0F, 2 * utils::math::PI);
}
}    // namespace intent
}    // namespace cooboc