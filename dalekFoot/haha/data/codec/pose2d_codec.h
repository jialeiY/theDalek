#ifndef __DATA_CODEC_POSE2D_CODEC_H__
#define __DATA_CODEC_POSE2D_CODEC_H__

#include "data/defs/pose2d.h"
#include "gen/data/proto/pose2d.pb.h"

namespace cooboc {
namespace data {
proto::Pose2D convert(const data::Pose2D &);
}    // namespace data
}    // namespace cooboc

#endif
