#include "framework/timer_thread.h"

#include "framework/watchdog_thread.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "framework/event_type.h"

using namespace std;

TimerThread::TimerThread(const ThreadHub &hub) : IThread(hub)
{
}

TimerThread::~TimerThread()
{
}

void TimerThread::onNotify(EventType eventType)
{
}

void TimerThread::work()
{
    notify("watchdog", EventType::GLOBAL_CYCLE_START);
    notify("io", EventType::GLOBAL_CYCLE_START);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    notify("watchdog", EventType::IO_MCU_RESPONSE_TIMEOUT);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}
