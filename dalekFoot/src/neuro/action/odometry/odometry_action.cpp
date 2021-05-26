#include "action/odometry/odometry_action.h"
#include "module/sensing/wheel_sensor/wheel_sensor.h"
#include "logger/logger.h"
#include "module/data_types/sensing/wheel_status.h"
#include <string>

namespace action {
namespace odometry {


OdometryAction::OdometryAction(const std::string &name, framework::EntityAgency &entityAgency) :
	IAction(name, entityAgency) {
		
}


OdometryAction::~OdometryAction() {

}


void OdometryAction::execute(void) {
	// Odometry need wheelSensor
	sensing::wheel_sensor::WheelSensor *wheel = dynamic_cast<sensing::wheel_sensor::WheelSensor *>(mAgency.getSensor("wheel"));
	
	sensing::WheelStatus wheelStatus = wheel->getWheelStatus();
	// copy to local just for debug
	mOdometry.value = wheelStatus.encoder[3];
	mSpeed = mOdometry.value - mPreviousEncoderValue;
	mPreviousEncoderValue = mOdometry.value;

	LogInfo("step %d", mSpeed);

}


}
}