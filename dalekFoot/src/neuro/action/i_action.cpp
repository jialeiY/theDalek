#include "action/i_action.h"
#include "framework/thread/entity_agency.h"
#include <string>

namespace action {


IAction::IAction(const std::string &name, framework::thread::EntityAgency &entityAgency) :
	mAgency(entityAgency),
	mSensorData(nullptr),
	mOutputData(nullptr) {
	entityAgency.registerAction(name, this);
}


void IAction::setExchangeMemoryArea(data_types::ActionData *actionData) {
	mOutputData = actionData;
}

}