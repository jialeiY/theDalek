#ifndef __INTENTS_TOPICS_BEHAVIOR_TOPIC_H__
#define __INTENTS_TOPICS_BEHAVIOR_TOPIC_H__

#include <cstdint>
#include "data/defs/polar_vector2d.h"
#include "data/defs/position2d.h"

namespace cooboc {
namespace intent {


struct BehaviorTopic {
    using BehaviorId = std::uint32_t;
    enum class BehaviorTask : std::int32_t {
        STOP = 0,
        MOVE = 1,
    };

    struct BehaviorMoveRequest {
        data::Position2D from {};
        data::Position2D to {};
        data::PolarVector2D targetVelocity {};
    };

    BehaviorId id {0U};
    BehaviorTask task {BehaviorTask::STOP};
    BehaviorMoveRequest moveRequest {};
};

}    // namespace intent
}    // namespace cooboc

#endif
