#ifndef __DATA_DODEC_ROUTE_SEGMENT_CODEC_H__
#define __DATA_DODEC_ROUTE_SEGMENT_CODEC_H__

#include "data/defs/route_segment.h"
#include "gen/data/proto/route_segment.pb.h"

namespace cooboc {
namespace data {
proto::RouteSegment convert(const data::RouteSegment &);
}    // namespace data
}    // namespace cooboc


#endif