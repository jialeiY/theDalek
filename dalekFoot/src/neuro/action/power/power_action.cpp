#include "action/power/power_action.h"
#include "module/sensing/wheel_sensor/wheel_sensor.h"
#include "logger/logger.h"
#include "module/data_types/sensing/wheel_sensor_data.h"
#include <string>

namespace action {
namespace power {


PowerAction::PowerAction(const std::string &name, framework::EntityAgency &entityAgency) :
	IAction(name, entityAgency) {
	
}


PowerAction::~PowerAction() {

}


void PowerAction::execute(void) {
	LogInfo("speed from sensor: %f", (mSensorData->wheel)[3].speed);
	

}


}
}