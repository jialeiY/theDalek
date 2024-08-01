#include "intents/odometry_intent/odometry_intent.h"
#include <random>
#include "intents/topics/topics.h"

namespace cooboc {
namespace intent {
OdometryIntent::OdometryIntent() :
    randomDev_ {},
    randomGen_ {randomDev_()},
    randomDistribution_ {0.0F, 0.2F} {}

OdometryIntent::~OdometryIntent() {}

void OdometryIntent::setup() {
    odometryTopic.pose.position.x  = 0.0F;
    odometryTopic.pose.position.y  = 0.0F;
    odometryTopic.pose.orientation = 0.0F;
}


void OdometryIntent::tick() {
    odometryTopic.pose.position.x  = randomDistribution_(randomGen_);
    odometryTopic.pose.position.y  = randomDistribution_(randomGen_);
    odometryTopic.pose.orientation = randomDistribution_(randomGen_) * 5.4F;
}
}    // namespace intent
}    // namespace cooboc