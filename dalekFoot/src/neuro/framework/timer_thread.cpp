#include "framework/timer_thread.h"
#include "logger/logger.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "framework/event_type.h"

namespace framework {

TimerThread::TimerThread(const ThreadHub &hub) : IThread(hub)
{
}

TimerThread::~TimerThread()
{
}

void TimerThread::onNotify(EventType eventType, void *data)
{
}

void TimerThread::work()
{
	notify("io", EventType::GLOBAL_CYCLE_START);
	notify("control", EventType::GLOBAL_CYCLE_START);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));

}


}