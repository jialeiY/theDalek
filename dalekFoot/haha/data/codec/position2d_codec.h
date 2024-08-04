#ifndef __DATA_CODEC_POSITION2D_CODEC_H__
#define __DATA_CODEC_POSITION2D_CODEC_H__

#include "data/codec/vector2d_codec.h"
#include "data/defs/position2d.h"
#include "data/proto/position2d.h"

namespace cooboc {
namespace data {

proto::Position2D convert(const data::Position2D &);

}    // namespace data
}    // namespace cooboc

#endif
