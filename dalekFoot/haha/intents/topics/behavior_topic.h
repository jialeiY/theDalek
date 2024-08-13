#ifndef __INTENTS_TOPICS_BEHAVIOR_TOPIC_H__
#define __INTENTS_TOPICS_BEHAVIOR_TOPIC_H__

#include "data/defs/polar_vector2d.h"
#include "data/defs/position2d.h"

namespace cooboc {
namespace intent {

struct BehaviorTopic {
    // TODO: specify the target is speed, time or position priority

    data::Position2D fromPosition {};
    data::Position2D targetPosition {};
    data::PolarVector2D targetVelocity {};
};

}    // namespace intent
}    // namespace cooboc

#endif
