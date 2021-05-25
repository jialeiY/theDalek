#include "framework/entity_agency.h"
#include "string.h"
#include <vector>

namespace framework {



EntityAgency::EntityAgency()
{
}

EntityAgency::~EntityAgency()
{
}



hardware::IHardware * EntityAgency::getHardware(const std::string &name) const {
	const auto iter = mHardwareMap.find(name);
	return iter == mHardwareMap.end() ? nullptr : iter->second;
}



std::vector<hardware::IHardware *> EntityAgency::getHardwareList(void) const {
	std::vector<hardware::IHardware *> ret;
	for (const auto & hdPair : mHardwareMap) {
		ret.push_back(hdPair.second);
	}
	return ret;
}

action::IAction *EntityAgency::getAction(const std::string &name) const {
	const auto iter = mActionMap.find(name);
	return iter == mActionMap.end() ? nullptr : iter->second;
}

}