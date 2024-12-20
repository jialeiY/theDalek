#ifndef __COMMON_DATA_DEFS_ENCODER_READING_TOPIC_H__
#define __COMMON_DATA_DEFS_ENCODER_READING_TOPIC_H__

#include <cstdint>
#include "common/data_defs/qualifier.h"
#include "common/data_defs/timepoint.h"


namespace cooboc {
namespace data {


struct EncoderReading {
    std::uint16_t value {0U};
    Qualifier qualifier {Qualifier::BAD};
};


struct EncoderReadingTopic {
    EncoderReadingTopic() : timestamp {}, encoder {} {}
    Timepoint timestamp {};
    Qualifier qualifier {Qualifier::BAD};
    cooboc::data::EncoderReading encoder[4U] {};
};

}    // namespace data
}    // namespace cooboc

#endif
