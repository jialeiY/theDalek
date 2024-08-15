#ifndef __DATA_CODEC_ROUTE_CURVATURE_DISTRIBUTION_CODEC_H__
#define __DATA_CODEC_ROUTE_CURVATURE_DISTRIBUTION_CODEC_H__

#include "data/defs/route_curvature_distribution.h"
#include "gen/data/proto/route_curvature_distribution.pb.h"

namespace cooboc {
namespace data {

proto::CurvatureDistribution convert(const CurvatureDistribution &in);


}    // namespace data
}    // namespace cooboc

#endif
