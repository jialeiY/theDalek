#ifndef __ACTION_I_ACTION_H__
#define __ACTION_I_ACTION_H__


#include "module/data_types/action_data.h"
#include "module/data_types/sensor_data.h"
#include <string>
#include <cstdint>
namespace framework {
namespace thread {
	class EntityAgency;
}
}


namespace action {



class IAction {
	public:
		IAction(const std::string &name, framework::thread::EntityAgency &entityAgency);
		virtual ~IAction() {};
		virtual void execute(std::uint64_t cycleCount) = 0;
		virtual void setSensorData(data_types::SensorData *sensorData) {
			mSensorData = sensorData;
		}
		virtual void setExchangeMemoryArea(data_types::ActionData *actionData);
	protected:
		framework::thread::EntityAgency & mAgency;
		data_types::SensorData *mSensorData;
		data_types::ActionData *mOutputData;
};


}


#endif
