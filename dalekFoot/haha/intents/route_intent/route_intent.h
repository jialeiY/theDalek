#ifndef __INTENTS_ROUTE_INTENT_ROUTE_INTENT_H__
#define __INTENTS_ROUTE_INTENT_ROUTE_INTENT_H__

#include "intents/intent_base.h"
#include "intents/topics/behavior_topic.h"
#include "intents/topics/route_topic.h"

namespace cooboc {
namespace intent {
class RouteIntent : public IntentBase {
  public:
    RouteIntent();
    virtual ~RouteIntent();
    virtual void setup();
    virtual void tick();

  private:
    intent::RouteTopic routeTopic_ {};


    // bool needGenerateNewRoute();
    void invalidateOutput();
    void checkAndMakeRoute(const intent::BehaviorTopic& behaviorTopic);
    void makeRoute(const intent::BehaviorTopic& behaviorTopic);
    data::RouteId makeNewRouteId();
};
}    // namespace intent
}    // namespace cooboc

#endif
