#include "data/codec/route_curvature_distribution_codec.h"

namespace cooboc {
namespace data {
proto::CurvatureDistribution convert(const CurvatureDistribution &in) {
    proto::CurvatureDistribution out;

    out = static_cast<proto::CurvatureDistribution>(in);

    return out;
}
}    // namespace data
}    // namespace cooboc