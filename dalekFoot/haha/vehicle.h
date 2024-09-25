#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "data/defs/vehicle_response.h"
#include "intents/topics/vehicle_request_topic.h"

namespace cooboc {
namespace vehicle {

// Abstract interface
class Vehicle {
  public:
    void setup();
    void setRequest(const cooboc::intent::VehicleRequestTopic &vehicleRequestTopic);
    void tick();
    cooboc::data::VehicleResponse getResponse();
};

}    // namespace vehicle
}    // namespace cooboc

#endif
