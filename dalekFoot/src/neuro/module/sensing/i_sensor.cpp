#include "module/sensing/i_sensor.h"
#include "framework/thread/entity_agency.h"
#include <string>

namespace sensing {

ISensor::ISensor(const std::string &name, framework::thread::EntityAgency &entityAgency) :
	mOutputData(nullptr) {
	entityAgency.registerSensor(name, this);
};

void ISensor::setExchangeMemoryArea(data_types::SensorData *sensorData) {
	mOutputData = sensorData;
}
}