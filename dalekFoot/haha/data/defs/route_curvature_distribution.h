
#ifndef __DATA_DEFS_ROUTE_CURVATURE_DISTRIBUTION_H__
#define __DATA_DEFS_ROUTE_CURVATURE_DISTRIBUTION_H__


#include <cstdint>


namespace cooboc {
namespace data {

enum class CurvatureDistribution : std::uint8_t {
    // Only consider the segment before this segment note valid for first vertex
    CONSIDER_PREVIOUS = 0,
    // Only consider the segment after this vertex, not valid for end vertex
    CONSIDER_NEXT = 1,
    // Not valid for first vertex
    CONSIDER_BOTH = 2,
    // the circle, constant at next segment
    CONSTANT_NEXT = 3,
    DONT_CARE     = 4,
};

}    // namespace data
}    // namespace cooboc

#endif
