#include "action/power/power_action.h"
#include "module/sensing/wheel_sensor/wheel_sensor.h"
#include "logger/logger.h"
#include "module/data_types/sensing/wheel_sensor_data.h"
#include <string>
#include <cstdint>
#include <cmath>
#include <algorithm>

namespace action {
namespace power {


PowerAction::PowerAction(const std::string &name, framework::thread::EntityAgency &entityAgency) :
	IAction(name, entityAgency),
	mErrorSum(0.0F),
	mLastError(0.0F) {
	
}


PowerAction::~PowerAction() {

}


void PowerAction::execute(std::uint64_t cycleCount) {
	constexpr float target {0.2F};
	const float currentSpeed = (mSensorData->wheel)[3].speed;
	const float currentError = target - currentSpeed;

	if (cycleCount > 5) {
		const float p =  target / 0.007F + 5.5F;
		
		mErrorSum += currentError;
		// mErrorSum = std::min(mErrorSum, 2.0F);
		const float i = mErrorSum * 25.0;

		const float d = (currentError - mLastError) * 5.10; 
		
		float pid = p + i + d;
		
		pid = std::min(pid, 100.0F);
		pid = std::min(pid, 50.0F);
		pid = std::max(pid, 0.0F);
		// LogInfo("speed from sensor: %f, pid: %f, P:%f I:%f D:%f", (mSensorData->wheel)[3].speed, pid, p, i, d);
		
		mOutputData->power.value = std::round(pid);
	}
	mLastError = currentError;
}


}
}