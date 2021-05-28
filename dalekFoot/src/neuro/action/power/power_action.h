#ifndef __ACTION_POWER_POWER_ACTION_H__
#define __ACTION_POWER_POWER_ACTION_H__

#include "action/i_action.h"
#include "framework/entity_agency.h"

namespace action {
namespace power {

class PowerAction : public IAction {
	public:
		PowerAction(const std::string &name, framework::EntityAgency &entityAgency);
		virtual ~PowerAction();
		virtual void execute(void);
	
};

}
}



#endif
