#ifndef __INTENTS_ROUTE_PROVISION_INTENT_ROUTE_PROVISION_INTENT_H__
#define __INTENTS_ROUTE_PROVISION_INTENT_ROUTE_PROVISION_INTENT_H__

#include "intents/intent_base.h"
#include "intents/topics/route_topic.h"

namespace cooboc {
namespace intent {
class RouteProvisionIntent : public IntentBase {
  public:
    RouteProvisionIntent();
    virtual ~RouteProvisionIntent();
    virtual void setup();
    virtual void tick();

  private:
    RouteId uniqueRouteId_ {0U};
};
}    // namespace intent
}    // namespace cooboc

#endif
