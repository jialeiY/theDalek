#include "framework/control_thread.h"
#include "framework/event_type.h"
#include "framework/entity_agency.h"
#include "logger/logger.h"
#include "module/mem/mem.h"

namespace framework {


ControlThread::ControlThread(const ThreadHub &hub, const EntityAgency &agency) : 
	IThread(hub), 
	mExchangeAreaPtr(nullptr),
	mAgency(agency) {
}

ControlThread::~ControlThread() {
}

void ControlThread::onNotify(EventType eventType, volatile void *data) {
	mExchangeAreaPtr = static_cast<volatile data_types::ExchangeArea *>(data);
	// copy to local memory
	data_types::ExchangeArea localData;
	mem::memcpy(&localData, mExchangeAreaPtr, sizeof(struct data_types::ExchangeArea));
	// LogInfo("on notifiy of contorl: %x", mExchangeAreaPtr);
	LogInfo("read from sensor: %d %d %d %d", 
		localData.input.mcuSensors.motorEncoder[0],
		localData.input.mcuSensors.motorEncoder[1],
		localData.input.mcuSensors.motorEncoder[2],
		localData.input.mcuSensors.motorEncoder[3]);
}

void ControlThread::work() {
	
}


}

