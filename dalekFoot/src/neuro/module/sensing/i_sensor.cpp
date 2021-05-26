#include "module/sensing/i_sensor.h"
#include "framework/entity_agency.h"
#include <string>

namespace sensing {

ISensor::ISensor(const std::string &name, framework::EntityAgency &entityAgency) {
	entityAgency.registerSensor(name, this);
};
}