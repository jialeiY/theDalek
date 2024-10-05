#include "intents/behavior_intent/behavior_intent.h"
#include <cmath>
#include <cstdint>
#include <cstdio>
#include "data/defs/polar_vector2d.h"
#include "data/defs/position2d.h"
#include "intents/topics/topics.h"
#include "utils/math.h"
#include "utils/time.h"

namespace cooboc {
namespace intent {


BehaviorIntent::BehaviorIntent() :
    behaviorTopic_ {},
    lastStopBehaviorId_ {data::kInvalidBehaviorId},
    lastMotionBehaviorId_ {data::kInvalidBehaviorId} {}

BehaviorIntent::~BehaviorIntent() {}

void BehaviorIntent::setup() {
    behaviorTopic.id   = data::kInvalidBehaviorId;
    behaviorTopic.task = BehaviorTopic::BehaviorTask::STOP;

    behaviorTopic.moveRequest = {
      .from           = data::Position2D {0.0F, 0.0F},
      .to             = data::Position2D {0.0F, 0.0F},
      .targetVelocity = data::PolarVector2D {0.0F, 0.0F},
    };
}

void BehaviorIntent::tick() {
    const data::Position2D &egoPosition {odometryTopic.pose.position};

    constexpr data::Position2D targetPosition {1.0F, 0.0F};

    // For development only
    bool targetReached = false;
    if (targetPosition.distance(egoPosition) < 0.5F) {
        targetReached = true;
    }

    if (targetReached) {
        outputStopBehavior();

    } else {
        outputMotionBehavior();
    }

    behaviorTopic = behaviorTopic_;
    std::printf("behavior_ to x: %f\r\n", behaviorTopic_.moveRequest.to.x);
    std::printf("behavior to x: %f\r\n", behaviorTopic.moveRequest.to.x);

    // // cycle = 1S
    // std::uint64_t milli {utils::time::milliseconds()};
    // milli %= 1000ULL;

    // float x = std::cos(static_cast<float>(milli) * 2.0F * utils::math::PI / 1000.0F);
    // float y = std::sin(static_cast<float>(milli) * 2.0F * utils::math::PI / 1000.0F);

    // behaviorTopic.targetPosition.x = 0.500F * x;
    // behaviorTopic.targetPosition.y = 0.500F * y;


    // std::uint64_t fromm = utils::time::milliseconds();
    // fromm *= 3.27;
    // fromm %= 373;

    // float ix = std::cos(static_cast<float>(fromm) * 2.0F * utils::math::PI / 373.0F);
    // float iy = std::sin(static_cast<float>(fromm) * 2.0F * utils::math::PI / 373.0F);
    // behaviorTopic.fromPosition.x = 0.08 * ix;
    // behaviorTopic.fromPosition.y = 0.12 * iy;
}

data::BehaviorId BehaviorIntent::makeNewBehaviorId() {
    static data::BehaviorId id {1U};
    return id++;
}

void BehaviorIntent::outputStopBehavior() {
    const bool isLastOutputIdValid = data::isValid(lastStopBehaviorId_);
    const bool isLastTopicIdValid  = data::isValid(behaviorTopic_.id);
    const bool isLastOutputIdSame  = lastStopBehaviorId_ == behaviorTopic_.id;

    bool canSkipOutput = (isLastOutputIdValid && isLastTopicIdValid) && isLastOutputIdSame;
    if (canSkipOutput) {
        std::printf("skip\r\n");
        return;
    }
    std::printf("make\r\n");

    const data::BehaviorId newBehaviorId = makeNewBehaviorId();

    behaviorTopic_.id   = newBehaviorId;
    lastStopBehaviorId_ = newBehaviorId;
    behaviorTopic.task  = BehaviorTopic::BehaviorTask::STOP;
}

void BehaviorIntent::outputMotionBehavior() {
    // Only for debug now

    const bool isLastOutputIdValid = data::isValid(lastMotionBehaviorId_);
    const bool isLastTopicIdValid  = data::isValid(behaviorTopic_.id);
    const bool isLastOutputIdSame  = lastMotionBehaviorId_ == behaviorTopic_.id;
    bool canSkipOutput = (isLastOutputIdValid && isLastTopicIdValid) && isLastOutputIdSame;
    if (canSkipOutput) {
        return;
    }

    const data::BehaviorId newBehaviorId = makeNewBehaviorId();

    behaviorTopic_.id                         = newBehaviorId;
    lastMotionBehaviorId_                     = newBehaviorId;
    behaviorTopic_.task                       = BehaviorTopic::BehaviorTask::MOVE;
    behaviorTopic_.moveRequest.from           = {0.0F, 0.0F};
    behaviorTopic_.moveRequest.to             = {1.0F, 1.0F};
    behaviorTopic_.moveRequest.targetVelocity = {0.0F, 0.0F};
}


}    // namespace intent
}    // namespace cooboc