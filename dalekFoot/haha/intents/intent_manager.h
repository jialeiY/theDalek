#ifndef __INTENTS_INTENT_MANAGER_H__
#define __INTENTS_INTENT_MANAGER_H__

#include <intents/intent_base.h>
#include <vector>
#include "data/defs/vehicle_response.h"

namespace cooboc {
namespace intent {


class IntentManager {
  public:
    IntentManager();
    virtual ~IntentManager();
    void setup();

    void updateVehicleResponse(data::VehicleResponse vehicleResponse);
    void tick();


  private:
    std::vector<IntentBase *> intents_;
};
}    // namespace intent
}    // namespace cooboc

#endif
