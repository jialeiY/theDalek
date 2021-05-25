#ifndef __FRAMEWORK_ENTITY_AGENCY_H__
#define __FRAMEWORK_ENTITY_AGENCY_H__


#include "action/i_action.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace hardware {
	class IHardware;
}
namespace framework {

class EntityAgency {
public:
	EntityAgency();
	virtual ~EntityAgency();
	inline void registerHardware(const std::string &name, hardware::IHardware *hardware) { mHardwareMap[name] = hardware; }
	inline void registerAction(const std::string &name, action::IAction *action) {mActionMap[name] = action;}
	hardware::IHardware *getHardware(const std::string &name) const;
	std::vector<hardware::IHardware *> getHardwareList(void) const;
	action::IAction *getAction(const std::string &name) const;

private:
	std::unordered_map<std::string, hardware::IHardware *> mHardwareMap;
	std::unordered_map<std::string, action::IAction *> mActionMap;
	
};

}

#endif
