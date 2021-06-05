#ifndef __FRAMEWORK_RTDP_PERSISTENT_WRITER_HANDLER_H__
#define __FRAMEWORK_RTDP_PERSISTENT_WRITER_HANDLER_H__

#include "framework/rtdp/persistent/writer_thread.h"
#include "module/data_types/hardware_data.h"

namespace framework {
namespace rtdp {
namespace persistent {
namespace detail {
static inline void writeHandware(const data_types::HardwareData *data)  {
	framework::rtdp::persistent::writerThread.requestWriteHardwareData(data);
}

static inline void dummyFun(...) {}


}
}
}
}


// #define WritePersistentHardwareData framework::rtdp::persistent::detail::dummyFun
#define WritePersistentHardwareData framework::rtdp::persistent::detail::writeHandware


#endif

