#ifndef __INTENTS_TOPICS_EGO_STATE_TOPIC_H__
#define __INTENTS_TOPICS_EGO_STATE_TOPIC_H__

#include "data/defs/polar_vector2d.h"

namespace cooboc {
namespace intent {
struct EgoStateTopic {
    data::PolarVector2D velocity {};        // Ego coordinate m/s
    data::PolarVector2D acceleration {};    // Ego coordinate m/s2
    float angularVelocity {0.0F};           // rad/s
    float angularAcceleration {0.0F};       // rad/s2
};
}    // namespace intent

}    // namespace cooboc


#endif
