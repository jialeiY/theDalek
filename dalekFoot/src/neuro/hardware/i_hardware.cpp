#include "hardware/i_hardware.h"
#include "framework/entity_agency.h"
#include <string>

namespace hardware {

IHardware::IHardware(const std::string &name, framework::EntityAgency &entityAgency) {
	entityAgency.registerHardware(name, this);
};
}