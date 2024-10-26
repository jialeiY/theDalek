#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "data/gh_protocol.h"

namespace cooboc {
namespace vehicle {

// Abstract interface
class Vehicle {
  public:
    void setup();
    void setRequest(const comm::HGPacket &hgPacket);
    void tick();
    const cooboc::comm::GHPacket &getResponse() const;
};

}    // namespace vehicle
}    // namespace cooboc

#endif
