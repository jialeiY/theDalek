#include "data/codec/pose2d_codec.h"
#include "data/codec/vector2d_codec.h"
#include "data/defs/pose2d.h"
#include "gen/data/proto/pose2d.pb.h"

namespace cooboc {
namespace data {
proto::Pose2D convert(const data::Pose2D &in) {
    proto::Pose2D out;
    *out.mutable_position() = convert(in.position);
    out.set_orientation(in.orientation);
    return out;
}
}    // namespace data
}    // namespace cooboc
