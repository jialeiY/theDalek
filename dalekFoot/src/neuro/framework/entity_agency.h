#ifndef __FRAMEWORK_ENTITY_AGENCY_H__
#define __FRAMEWORK_ENTITY_AGENCY_H__

#include "hardware/i_hardware.h"
#include <string>
#include <unordered_map>

class EntityAgency {
public:
	EntityAgency();
	virtual ~EntityAgency();
	inline void registerHardware(const std::string &name, hardware::IHardware *hardware) { mHardwareMap[name] = hardware; }
	hardware::IHardware *getHardware(const std::string &name) const;
private:
	std::unordered_map<std::string, hardware::IHardware *> mHardwareMap;
};

#endif
