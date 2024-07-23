#ifndef __COMMON_DATA_DEF_ENCODER_READING_TRIGGER_TOPIC_H__
#define __COMMON_DATA_DEF_ENCODER_READING_TRIGGER_TOPIC_H__

#include <cstdint>
#include "common/data_defs/timepoint.h"

namespace cooboc {
namespace data {
struct EncoderReadingTriggerTopic {
    Timepoint timestamp;
    bool isTriggerSuccessful;
};
}    // namespace data
}    // namespace cooboc

#endif
