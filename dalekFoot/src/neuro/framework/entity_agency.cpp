#include "framework/entity_agency.h"
#include "string.h"

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