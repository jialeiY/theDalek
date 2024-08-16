
#ifndef __DATA_DEFS_ROUTE_CURVATURE_DISTRIBUTION_H__
#define __DATA_DEFS_ROUTE_CURVATURE_DISTRIBUTION_H__


#include <cstdint>


namespace cooboc {
namespace data {

enum class CurvatureDistribution : std::uint8_t {
    FOLLOW_PREDECESSOR = 0,
    FOLLOW_SUCCESSOR   = 1,
    CONSIDER_BOTH      = 2,
    CONSTANT            = 3,    // the circle
    DONT_CARE          = 4,
};

}    // namespace data
}    // namespace cooboc

#endif
