#ifndef __MODULE_SENSING_I_SENSOR_H__
#define __MODULE_SENSING_I_SENSOR_H__

#include "module/data_types/hardware_data.h"

#include <string>


namespace framework {
	class EntityAgency;
}


namespace sensing {

class ISensor {
	public:
		ISensor(const std::string &name, framework::EntityAgency &entityAgency);
		virtual ~ISensor() {};

		virtual void updateFromSensor(const data_types::HardwareData &inputData) = 0;

	

};


}
#endif

