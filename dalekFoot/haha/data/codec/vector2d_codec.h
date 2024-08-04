#ifndef __DATA_CODEC_VECTOR2D_CODEC_H__
#define __DATA_CODEC_VECTOR2D_CODEC_H__

#include "data/defs/vector2d.h"
#include "gen/data/proto/vector2d.pb.h"

namespace cooboc {
namespace data {

proto::Vector2D convert(const data::Vector2D &);

}    // namespace data
}    // namespace cooboc

#endif
