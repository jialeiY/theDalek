#ifndef __INTENTS_TOPICS_PLANNING_REQUEST_TOPIC_H__
#define __INTENTS_TOPICS_PLANNING_REQUEST_TOPIC_H__

namespace cooboc {
namespace intent {

struct PlanningRequestTopic {
    float targetPositionX {0.0F};
    float targetPositionY {0.0F};

    float targetVelocityX {0.0F};
    float targetVelocityY {0.0F};
    float targetVelocitySpeed {0.0F};
};

}    // namespace intent
}    // namespace cooboc

#endif
