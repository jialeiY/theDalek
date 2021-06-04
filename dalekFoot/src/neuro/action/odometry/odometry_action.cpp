#include "action/odometry/odometry_action.h"
#include "module/sensing/wheel_sensor/wheel_sensor.h"
#include "framework/rtdp/logger/logger.h"
#include "module/data_types/sensing/wheel_sensor_data.h"
#include <string>
#include <cstdint>

namespace action {
namespace odometry {


OdometryAction::OdometryAction(const std::string &name, framework::thread::EntityAgency &entityAgency) :
	IAction(name, entityAgency) {
	
}


OdometryAction::~OdometryAction() {

}


void OdometryAction::execute(std::uint64_t cycleCount) {
	
	
	/*
	sensing::WheelStatus wheelStatus = wheel->getWheelStatus();
	// copy to local just for debug
	mOdometry.value = wheelStatus.encoder[3];
	mSpeed = mOdometry.value - mPreviousEncoderValue;
	mPreviousEncoderValue = mOdometry.value;

	// LogInfo("step %d", mSpeed);
	*/
	
}


}
}