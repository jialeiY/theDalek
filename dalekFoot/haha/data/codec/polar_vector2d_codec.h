#ifndef __DATA_CODEC_POLAR_VECTOR2D_CODEC_H__
#define __DATA_CODEC_POLAR_VECTOR2D_CODEC_H__

#include "data/defs/polar_vector2d.h"
#include "gen/data/proto/polar_vector2d.pb.h"

namespace cooboc {
namespace data {

proto::PolarVector2D convert(const data::PolarVector2D &);

}
}    // namespace cooboc

#endif
