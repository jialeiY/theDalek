#include "data/codec/planning_request_topic_codec.h"
#include "data/codec/polar_vector2d_codec.h"
#include "data/codec/position2d_codec.h"
#include "gen/data/proto/planning_request_topic.pb.h"
#include "intents/topics/planning_request_topic.h"

namespace cooboc {
namespace data {

proto::PlanningRequestTopic convert(const intent::PlanningRequestTopic &in) {
    proto::PlanningRequestTopic out;

    *out.mutable_fromposition()   = convert(in.fromPosition);
    *out.mutable_targetposition() = convert(in.targetPosition);
    *out.mutable_targetvelocity() = convert(in.targetVelocity);
    return out;
}


}    // namespace data
}    // namespace cooboc