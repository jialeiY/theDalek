#include "intents/reference_path_intent/components/vertex_property.h"
#include "intents/topics/route_topic.h"
#include "test/utest.h"

UTEST(ReferencePathIntentTest, RouteProfileSmokeTest) {
    cooboc::intent::RouteTopic routeTopic {};
    cooboc::intent::reference_path::RouteProfile routeProfile {};
    cooboc::intent::reference_path::updateRouteProfile(routeTopic, routeProfile);
}