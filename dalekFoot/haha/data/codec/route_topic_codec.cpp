#include "data/codec/route_topic_codec.h"
#include <cstdint>
#include "data/codec/position2d_codec.h"
#include "data/codec/route_segment_codec.h"
#include "data/proto/position2d.h"
#include "gen/data/proto/route_topic.pb.h"
#include "intents/topics/route_topic.h"

namespace cooboc {
namespace data {

proto::RouteTopic convert(const intent::RouteTopic &in) {
    proto::RouteTopic out;
    out.set_hasvalue(in.hasValue);
    out.set_routeid(in.routeId);
    out.set_routesegmentsize(in.routeSegmentSize);

    proto::Position2D *startPoint = out.mutable_startpoint();
    *startPoint                   = convert(in.startPoint);


    for (std::size_t i {0U}; i < intent::RouteTopic::kPolylineCapacity; ++i) {
        proto::RouteSegment *routeSegment = out.add_routesegment();
        *routeSegment                     = convert(in.routeSegment[i]);
    }
    return out;
}

}    // namespace data
}    // namespace cooboc