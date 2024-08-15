#ifndef __DATA_DEFS_ROUTE_Segment_H__
#define __DATA_DEFS_ROUTE_Segment_H__

#include <cstdint>
#include "data/defs/position2d.h"
#include "data/defs/route_curvature_distribution.h"

namespace cooboc {
namespace data {


struct RouteSegment {
    Position2D endPoint {};
    CurvatureDistribution curvatureDistribution {};
};

}    // namespace data
}    // namespace cooboc


#endif
