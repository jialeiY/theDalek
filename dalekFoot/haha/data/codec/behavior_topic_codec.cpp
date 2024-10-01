#include "data/codec/behavior_topic_codec.h"
#include <type_traits>
#include "data/codec/polar_vector2d_codec.h"
#include "data/codec/position2d_codec.h"
#include "gen/data/proto/behavior_topic.pb.h"
#include "intents/topics/behavior_topic.h"

namespace cooboc {
namespace data {

static inline proto::BehaviorTask convert(const intent::BehaviorTopic::BehaviorTask &in) {
    static_assert(
      std::is_same<std::underlying_type<proto::BehaviorTask>::type,
                   std::underlying_type<intent::BehaviorTopic::BehaviorTask>::type>::value);
    return static_cast<proto::BehaviorTask>(in);
}

static inline proto::BehaviorMoveRequest convert(
  const intent::BehaviorTopic::BehaviorMoveRequest &in) {
    proto::BehaviorMoveRequest out;
    *out.mutable_from()           = convert(in.from);
    *out.mutable_to()             = convert(in.to);
    *out.mutable_targetvelocity() = convert(in.targetVelocity);
    return out;
}


proto::BehaviorTopic convert(const intent::BehaviorTopic &in) {
    proto::BehaviorTopic out;

    out.set_id(in.id);
    out.set_task(convert(in.task));
    *out.mutable_moverequest() = convert(in.moveRequest);
    return out;
}


}    // namespace data
}    // namespace cooboc