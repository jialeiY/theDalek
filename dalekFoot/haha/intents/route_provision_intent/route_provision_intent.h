#ifndef __INTENTS_ROUTE_PROVISION_INTENT_ROUTE_PROVISION_INTENT_H__
#define __INTENTS_ROUTE_PROVISION_INTENT_ROUTE_PROVISION_INTENT_H__

#include "intents/intent_base.h"

namespace cooboc {
namespace intent {
class RouteProvisionIntent : public IntentBase {
  public:
    RouteProvisionIntent();
    virtual ~RouteProvisionIntent();
    virtual void setup();
    virtual void tick();
};
}    // namespace intent
}    // namespace cooboc

#endif
