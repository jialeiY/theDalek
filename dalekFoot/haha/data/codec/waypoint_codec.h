#ifndef __DATA_CODEC_WAYPOINT_CODEC_H__
#define __DATA_CODEC_WAYPOINT_CODEC_H__

#include "data/defs/waypoint.h"
#include "gen/data/proto/waypoint.pb.h"

namespace cooboc {
namespace data {

proto::Waypoint convert(const data::Waypoint &);

}    // namespace data
}    // namespace cooboc

#endif
