#include "data/codec/passing_point_codec.h"
#include "data/codec/polar_vector2d_codec.h"
#include "data/codec/vector2d_codec.h"
#include "data/defs/passing_point.h"
#include "gen/data/proto/passing_point.pb.h"

namespace cooboc {
namespace data {
proto::PassingPoint convert(const data::PassingPoint &in) {
    proto::PassingPoint out;
    *out.mutable_position() = convert(in.position);
    *out.mutable_segment()  = convert(in.segment);
    return out;
}
}    // namespace data
}    // namespace cooboc
