#include "data/codec/ego_motion_state_topic_codec.h"
#include <cstdio>
#include "data/codec/polar_vector2d_codec.h"
#include "gen/data/proto/ego_motion_state_topic.pb.h"
#include "intents/topics/ego_motion_state_topic.h"

namespace cooboc {
namespace data {
proto::EgoMotionStateTopic convert(const intent::EgoMotionStateTopic &in) {
    proto::EgoMotionStateTopic out;
    *out.mutable_velocity()     = convert(in.velocity);
    *out.mutable_acceleration() = convert(in.acceleration);
    out.set_angularvelocity(in.angularVelocity);
    out.set_angularacceleration(in.angularAcceleration);
    return out;
}
}    // namespace data


}    // namespace cooboc
