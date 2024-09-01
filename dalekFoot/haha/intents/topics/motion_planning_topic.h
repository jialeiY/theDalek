#ifndef __INTENTS_TOPICS_MOTION_PLANNING_TOPIC_H__
#define __INTENTS_TOPICS_MOTION_PLANNING_TOPIC_H__

#include "data/defs/waypoint.h"
#include "intents/topics/common.h"

namespace cooboc {
namespace intent {


struct MotionPlanningTopic {
    data::Waypoint waypoints[kPlanningSize];
};

}    // namespace intent
}    // namespace cooboc


#endif
