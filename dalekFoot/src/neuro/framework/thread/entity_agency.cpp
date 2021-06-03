#include "framework/thread/entity_agency.h"
#include "module/sensing/i_sensor.h"
#include "string.h"
#include <vector>

namespace framework {
namespace thread {


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
	for (const auto & senPair : mSensorMap) {
		ret.push_back(senPair.second);
	}
	return ret;
}

action::IAction *EntityAgency::getAction(const std::string &name) const {
	const auto iter = mActionMap.find(name);
	return iter == mActionMap.end() ? nullptr : iter->second;
}

std::vector<action::IAction *> EntityAgency::getActionList(void) const {
	std::vector<action::IAction *> ret;
	for (const auto & actPair : mActionMap) {
		ret.push_back(actPair.second);
	}
	return ret;
}


}
}
