#include "data/codec/route_segment_codec.h"
#include "data/codec/position2d_codec.h"
#include "data/codec/route_curvature_distribution_codec.h"
#include "data/defs/route_segment.h"
#include "data/proto/position2d.h"
#include "gen/data/proto/route_segment.pb.h"


namespace cooboc {
namespace data {
proto::RouteSegment convert(const data::RouteSegment &in) {
    proto::RouteSegment out;
    proto::Position2D *endPoint = out.mutable_endpoint();
    *endPoint                   = convert(in.endPoint);

    out.set_curvaturedistribution(convert(in.curvatureDistribution));

    return out;
}
}    // namespace data
}    // namespace cooboc
