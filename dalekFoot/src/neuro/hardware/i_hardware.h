#ifndef __HARDWARE_I_HARDWARE_H__
#define __HARDWARE_I_HARDWARE_H__

#include "module/data_types/exchange_area.h"

#include <string>


namespace framework {
	class EntityAgency;
}


namespace hardware {

class IHardware {
	public:
		IHardware(const std::string &name, framework::EntityAgency &entityAgency);
		virtual ~IHardware() {};

		virtual void updateFromSensor(const data_types::ExchangeArea &inputData) = 0;

	

};


}
#endif

