#ifndef __ACTION_I_ACTION_H__
#define __ACTION_I_ACTION_H__


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
	protected:
		framework::EntityAgency & mAgency;
};


}


#endif
