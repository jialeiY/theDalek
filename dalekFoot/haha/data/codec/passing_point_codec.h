#ifndef __DATA_CODEC_PASSING_POINT_CODEC_H__
#define __DATA_CODEC_PASSING_POINT_CODEC_H__


#include "data/defs/passing_point.h"
#include "gen/data/proto/passing_point.pb.h"


namespace cooboc {
namespace data {
proto::PassingPoint convert(const data::PassingPoint &);
}    // namespace data
}    // namespace cooboc

#endif
