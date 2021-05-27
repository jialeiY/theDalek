#include "action/i_action.h"
#include "framework/entity_agency.h"
#include <string>

namespace action {


IAction::IAction(const std::string &name, framework::EntityAgency &entityAgency) :
	mAgency(entityAgency),
	mActionData(nullptr) {
	entityAgency.registerAction(name, this);
}


void IAction::setExchangeMemoryArea(data_types::ActionData *actionData) {
	mActionData = actionData;
}

}