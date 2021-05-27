#ifndef __FRAMEWORK_ENTITY_AGENCY_H__
#define __FRAMEWORK_ENTITY_AGENCY_H__


#include "action/i_action.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace sensing {
	class ISensor;
}
namespace framework {

class EntityAgency {
public:
	EntityAgency();
	virtual ~EntityAgency();
	inline void registerSensor(const std::string &name, sensing::ISensor *sensor) { mSensorMap[name] = sensor; }
	inline void registerAction(const std::string &name, action::IAction *action) {mActionMap[name] = action;}
	sensing::ISensor *getSensor(const std::string &name) const;
	std::vector<sensing::ISensor *> getSensorList(void) const;
	action::IAction *getAction(const std::string &name) const;
	std::vector<action::IAction *> getActionList(void) const;

private:
	std::unordered_map<std::string, sensing::ISensor *> mSensorMap;
	std::unordered_map<std::string, action::IAction *> mActionMap;
	
};

}

#endif
