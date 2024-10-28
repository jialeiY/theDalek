#include "data/codec/route_topic_codec.h"
#include <cstdint>
#include "data/codec/position2d_codec.h"
#include "data/codec/route_curvature_distribution_codec.h"
#include "data/codec/route_segment_codec.h"
#include "data/codec/static_polyline_pod_codec.h"
#include "data/proto/position2d.h"
#include "gen/data/proto/route_topic.pb.h"
#include "intents/topics/route_topic.h"

namespace cooboc {
namespace data {

proto::RouteTopic convert(const intent::RouteTopic &in) {
    proto::RouteTopic out;
    out.set_id(in.id);
    out.set_behaviorid(in.behaviorId);

    proto::StaticPolylinePod *polyline = out.mutable_polyline();
    *polyline                          = convert(in.polyline);

    for (std::size_t i {0U}; i < intent::RouteTopic::kPolylineCapacity; ++i) {
        out.add_connectivityproperties(convert(in.connectivityProperties[i]));
    }

    return out;
}

}    // namespace data
}    // namespace cooboc