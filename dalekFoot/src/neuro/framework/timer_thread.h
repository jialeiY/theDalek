#ifndef __FRAMEWORK_TIMEER_THREAD_H__
#define __FRAMEWORK_TIMEER_THREAD_H__

#include "framework/i_thread.h"
#include "framework/event_type.h"

class TimerThread : public IThread
{
public:
    TimerThread(const ThreadHub &hub);
    virtual ~TimerThread();

protected:
    virtual void onNotify(EventType eventType);

private:
    virtual void work();
};

#endif
