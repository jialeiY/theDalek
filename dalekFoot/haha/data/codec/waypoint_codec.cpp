#include "data/codec/waypoint_codec.h"
#include "data/codec/pose2d_codec.h"
#include "data/codec/vector2d_codec.h"
#include "data/defs/waypoint.h"
#include "gen/data/proto/waypoint.pb.h"


namespace cooboc {
namespace data {
proto::Waypoint convert(const data::Waypoint &in) {
    proto::Waypoint out;
    out.set_timepoint(in.timepoint);
    *out.mutable_pose()     = convert(in.pose);
    *out.mutable_velocity() = convert(in.velocity);

    out.set_velocityy(in.velocityY);
    out.set_accelerationy(in.accelerationY);

    return out;
}
}    // namespace data
}    // namespace cooboc