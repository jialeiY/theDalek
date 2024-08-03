#include "data/codec/route_topic_codec.h"
#include <cstdint>
#include "data/codec/position2d_codec.h"
#include "gen/data/proto/route_topic.pb.h"
#include "intents/topics/route_topic.h"

namespace cooboc {
namespace data {

proto::RouteTopic convert(const intent::RouteTopic &in) {
    proto::RouteTopic out;
    out.set_hasvalue(in.hasValue);
    out.set_routeid(in.routeId);
    out.set_polylinelength(in.polylineLength);
    for (std::size_t i {0U}; i < intent::RouteTopic::kPolylineLength; ++i) {
        proto::Position2D *position = out.add_polyline();
        *position                   = convert(in.polyline[i]);
    }
}

}    // namespace data
}    // namespace cooboc