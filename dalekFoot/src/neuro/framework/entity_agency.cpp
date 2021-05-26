#include "framework/entity_agency.h"
#include "module/sensing/i_sensor.h"
#include "string.h"
#include <vector>

namespace framework {



EntityAgency::EntityAgency()
{
}

EntityAgency::~EntityAgency()
{
}



sensing::ISensor * EntityAgency::getSensor(const std::string &name) const {
	const auto iter = mSensorMap.find(name);
	return iter == mSensorMap.end() ? nullptr : iter->second;
}



std::vector<sensing::ISensor *> EntityAgency::getSensorList(void) const {
	std::vector<sensing::ISensor *> ret;
	for (const auto & hdPair : mSensorMap) {
		ret.push_back(hdPair.second);
	}
	return ret;
}

action::IAction *EntityAgency::getAction(const std::string &name) const {
	const auto iter = mActionMap.find(name);
	return iter == mActionMap.end() ? nullptr : iter->second;
}

}