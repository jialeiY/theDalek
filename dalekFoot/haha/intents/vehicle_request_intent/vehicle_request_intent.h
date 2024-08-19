#ifndef __INTENTS_VEHICLE_REQUEST_INTENT_VEHICLE_REQUEST_INTENT_H__
#define __INTENTS_VEHICLE_REQUEST_INTENT_VEHICLE_REQUEST_INTENT_H__

#include "intents/intent_base.h"

namespace cooboc {
namespace intent {

class VehicleRequestIntent : public IntentBase {
  public:
    VehicleRequestIntent();
    virtual ~VehicleRequestIntent();
    virtual void setup() override;
    virtual void tick() override;
};


}    // namespace intent
}    // namespace cooboc
#endif
