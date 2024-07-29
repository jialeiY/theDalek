#ifndef __DATA_CODEC_POSITION2D_CODEC_H__
#define __DATA_CODEC_POSITION2D_CODEC_H__

#include "data/defs/position2d.h"
#include "gen/data/proto/position2d.pb.h"

namespace cooboc {
namespace data {

proto::Position2D convert(const data::Position2D &);

}
}    // namespace cooboc

#endif
