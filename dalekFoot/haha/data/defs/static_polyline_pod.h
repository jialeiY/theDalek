#ifndef __DATA_DEFS_STATIC_POLYLINE_POD_H__
#define __DATA_DEFS_STATIC_POLYLINE_POD_H__

#include <cstdint>
#include "data/defs/position2d.h"
#include "data/defs/static_vector_pod.h"

namespace cooboc {
namespace data {

template<std::size_t N>
using StaticPolylinePod = StaticVectorPod<data::Position2D, N>;


}    // namespace data
}    // namespace cooboc

#endif
