#ifndef __SIMULATOR_SIMULATOR_H__
#define __SIMULATOR_SIMULATOR_H__

#include "data/defs/vehicle_response.h"

namespace cooboc {
namespace sim {

// This is an Ideal model that can run any command
class Simulator {
  public:
    Simulator();
    virtual ~Simulator();
    void tick();
    data::VehicleResponse getVehicleResponse();

  private:
    data::VehicleResponse vehicleResponse_ {};
};

}    // namespace sim
}    // namespace cooboc

#endif
