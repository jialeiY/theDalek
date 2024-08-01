#ifndef __INTENTS_TOPICS_ODOMETRY_TOPIC_H__
#define __INTENTS_TOPICS_ODOMETRY_TOPIC_H__

#include "data/defs/pose2d.h"

namespace cooboc {
namespace intent {
struct OdometryTopic {
    data::Pose2D pose {};    // World coordinate
};
}    // namespace intent
}    // namespace cooboc

#endif
