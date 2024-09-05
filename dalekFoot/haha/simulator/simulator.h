#ifndef __SIMULATOR_SIMULATOR_H__
#define __SIMULATOR_SIMULATOR_H__

#include "data/defs/vehicle_response.h"
#include "intents/topics/vehicle_request_topic.h"


namespace cooboc {
namespace sim {

// This is an Ideal model that can run any command
class Simulator {
  public:
    Simulator();
    virtual ~Simulator();
    void setup();
    void tick();
    void updateVehicleRequest(const intent::VehicleRequestTopic &vehicleRequest);
    data::VehicleResponse getVehicleResponse();

  private:
    data::VehicleResponse vehicleResponse_ {};
};

}    // namespace sim
}    // namespace cooboc

#endif
