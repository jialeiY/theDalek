#ifndef __ACTION_I_ACTION_H__
#define __ACTION_I_ACTION_H__


#include "module/data_types/action_data.h"
#include <string>
namespace framework {
	class EntityAgency;
}


namespace action {



class IAction {
	public:
		IAction(const std::string &name, framework::EntityAgency &entityAgency);
		virtual ~IAction() {};
		virtual void execute(void) = 0;
		virtual void setMemoryArea(data_types::ActionData *actionData);
	protected:
		framework::EntityAgency & mAgency;
		data_types::ActionData *mActionData;
};


}


#endif
