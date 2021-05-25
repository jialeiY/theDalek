#include "action/odometry/odometry_action.h"
#include "hardware/wheel_sensor/wheel_sensor.h"
#include "logger/logger.h"
#include "module/data_types/hardware/wheelsensor.h"
#include <string>

namespace action {
namespace odometry {


OdometryAction::OdometryAction(const std::string &name, framework::EntityAgency &entityAgency) :
	IAction(name, entityAgency) {
		
}


OdometryAction::~OdometryAction() {

}


void OdometryAction::tick(void) {
	// Odometry need wheelSensor
	hardware::wheelsensor::WheelSensor *wheel = dynamic_cast<hardware::wheelsensor::WheelSensor *>(mAgency.getHardware("wheel"));
	
	hardware::wheelsensor::WheelStatus wheelStatus = wheel->getWheelStatus();
	// copy to local just for debug
	mOdometry.value = wheelStatus.encoder[3];
	mSpeed = mOdometry.value - mPreviousEncoderValue;
	mPreviousEncoderValue = mOdometry.value;

	LogInfo("step %d", mSpeed);

}


}
}