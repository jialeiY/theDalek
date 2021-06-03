#ifndef __ACTION_POWER_POWER_ACTION_H__
#define __ACTION_POWER_POWER_ACTION_H__

#include "action/i_action.h"
#include "framework/thread/entity_agency.h"
#include <cstdint>
namespace action {
namespace power {

class PowerAction : public IAction {
	public:
		PowerAction(const std::string &name, framework::thread::EntityAgency &entityAgency);
		virtual ~PowerAction();
		virtual void execute(std::uint64_t cycleCount);
	private:
		float mErrorSum;
		float mLastError;
	
};

}
}



#endif
