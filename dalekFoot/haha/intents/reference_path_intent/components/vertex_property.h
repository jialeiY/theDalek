#ifndef __INTENTS_REFERENCE_PATH_INTENT_COMPONENTS_VERTEX_PROPERTY_H__
#define __INTENTS_REFERENCE_PATH_INTENT_COMPONENTS_VERTEX_PROPERTY_H__

#include <array>
#include <vector>
#include "intents/topics/route_topic.h"

namespace cooboc {
namespace intent {
namespace reference_path {


// RouteProfile is the list for control points for each segment in route
using RouteProfile =
  std::array<std::vector<data::Position2D>, intent::RouteTopic::kMaxPolylineSegmentNumber>;

void updateRouteProfile(const RouteTopic &routeTopic, RouteProfile &routeProfile);

}    // namespace reference_path
}    // namespace intent
}    // namespace cooboc

#endif
