#ifndef __DATA_DEFS_ROUTE_ID_H__
#define __DATA_DEFS_ROUTE_ID_H__

#include <cstdint>

namespace cooboc {
namespace data {
using RouteId = std::uint64_t;
constexpr data::RouteId kInvalidRouteId {0U};
}    // namespace data
}    // namespace cooboc


#endif
