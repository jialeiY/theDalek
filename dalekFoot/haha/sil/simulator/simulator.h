#ifndef __SIL_SIMULATOR_SIMULATOR_H__
#define __SIL_SIMULATOR_SIMULATOR_H__

#include "data/gh_protocol.h"

namespace cooboc {
namespace sil {

// This is an Ideal model that can run any command
class Simulator {
  public:
    Simulator();
    virtual ~Simulator();
    void setup();
    void tick();
    void updateVehicleRequest(const comm::HGPacket &vehicleRequest);
    inline const comm::GHPacket &getVehicleResponse() const {
        return vehicleResponsePacket_;
    }

  private:
    alignas(4) comm::HGPacket vehicleRequestPacket_ {};
    alignas(4) comm::GHPacket vehicleResponsePacket_ {};


    float vehicleWheelSpeed_[4U] {};
    float vehicleWheelOdometry_[4U] {};
};

}    // namespace sil
}    // namespace cooboc

#endif
