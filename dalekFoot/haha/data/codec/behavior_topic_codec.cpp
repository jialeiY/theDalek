#include "data/codec/behavior_topic_codec.h"
#include "data/codec/polar_vector2d_codec.h"
#include "data/codec/position2d_codec.h"
#include "gen/data/proto/behavior_topic.pb.h"
#include "intents/topics/behavior_topic.h"

namespace cooboc {
namespace data {

proto::BehaviorTopic convert(const intent::BehaviorTopic &in) {
    proto::BehaviorTopic out;

    *out.mutable_fromposition()   = convert(in.fromPosition);
    *out.mutable_targetposition() = convert(in.targetPosition);
    *out.mutable_targetvelocity() = convert(in.targetVelocity);
    return out;
}


}    // namespace data
}    // namespace cooboc