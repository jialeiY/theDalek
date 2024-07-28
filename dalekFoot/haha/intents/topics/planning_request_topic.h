#ifndef __INTENTS_TOPICS_PLANNING_REQUEST_TOPIC_H__
#define __INTENTS_TOPICS_PLANNING_REQUEST_TOPIC_H__

#include "data/defs/position2d.h"
#include "data/defs/vector2d.h"

namespace cooboc {
namespace intent {

struct PlanningRequestTopic {
    data::Position2D fromPosition {};
    data::Position2D targetPosition {};
    data::Vector2D targetVelocity {};
};

}    // namespace intent
}    // namespace cooboc

#endif
