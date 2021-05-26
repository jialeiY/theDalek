#include "framework/io_thread.h"
#include "framework/event_type.h"
#include "module/math/crc.h"
#include "module/math/bitop.h"
#include "logger/logger.h"
#include "module/mem/mem.h"
#include <chrono>
#include <thread>
#include <iostream>

#include <unistd.h>
#include <cstring>


namespace framework {

volatile uint8_t m4speed = 0;

IOThread::IOThread(const ThreadHub &hub) : 
	IThread(hub),
	mStatus(IOStatus::IDLE),
	mDecoder(),
	mExchangeAreaPtr(nullptr)
{
	

}

IOThread::~IOThread() {
	
}

void IOThread::work() {
	
	switch (mStatus) {
		case (IOStatus::TRANSCEIVING): {

			break;
		}
		case (IOStatus::WORKING) : {
			usleep(50);
			break;
		}
		default: {
			mStatus = IOStatus::WORKING;
			// ERROR(unreachable status);
			break;
		}
	}
}

void IOThread::onNotify(EventType eventType, volatile void *data) {
	switch (eventType) {
		case (EventType::GLOBAL_CYCLE_START): {
			// output the data;
			
			mStatus = IOStatus::TRANSCEIVING;
			// printf("write data to mcu\r\n");
			
			break;
		}
		default: {
			break;
		}
	}
}

void IOThread::crcPayload() {
}



}