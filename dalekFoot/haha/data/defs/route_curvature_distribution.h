
#ifndef __DATA_DEFS_ROUTE_CURVATURE_DISTRIBUTION_H__
#define __DATA_DEFS_ROUTE_CURVATURE_DISTRIBUTION_H__


#include <cstdint>
#include <map>

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

const char* toString(CurvatureDistribution e) {
    static const std::map<CurvatureDistribution, const char*> enumStrings {
      {CurvatureDistribution::CONSIDER_PREVIOUS, "CONSIDER_PREVIOUS"},
      {CurvatureDistribution::CONSIDER_NEXT, "CONSIDER_NEXT"},
      {CurvatureDistribution::CONSIDER_BOTH, "CONSIDER_BOTH"},
      {CurvatureDistribution::CONSTANT_NEXT, "CONSTANT_NEXT"},
      {CurvatureDistribution::DONT_CARE, "DONT_CARE"},
    };

    auto it = enumStrings.find(e);
    return it == enumStrings.end() ? "Out of range" : it->second;
}


}    // namespace data
}    // namespace cooboc

#endif
