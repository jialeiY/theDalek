#ifndef __INTENTS_INTENT_MANAGER_H__
#define __INTENTS_INTENT_MANAGER_H__

#include <intents/intent_base.h>
#include <cstdint>
#include <vector>
#include "data/defs/vehicle_response.h"
#include "intents/topics/topics.h"
#include "intents/topics/vehicle_request_topic.h"
#include "utils/time.h"

namespace cooboc {
namespace intent {


class IntentManager {
  public:
    IntentManager();
    virtual ~IntentManager();
    void setup();

    void updateVehicleResponse(data::VehicleResponse vehicleResponse);
    inline const VehicleRequestTopic &getVehicleRequest() { return vehicleRequestTopic; }
    void tick();


  private:
    std::vector<IntentBase *> intents_;
    std::uint64_t tickCount_ {0U};
    std::uint64_t lastTickEndTime_ {0U};
    std::uint64_t lastTickDuration_ {0U};
};
}    // namespace intent
}    // namespace cooboc

#endif
