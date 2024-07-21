#ifndef __INTENTS_COMMON_DATA_DEFS_ENCODER_READING_OUTPUT_H__
#define __INTENTS_COMMON_DATA_DEFS_ENCODER_READING_OUTPUT_H__

#include <cstdint>

namespace cooboc {
namespace data {


struct EncoderReading {
    std::uint16_t value {0U};
};


struct EncoderReadingOutput {
    cooboc::data::EncoderReading encoder[4U];
};

}    // namespace data
}    // namespace cooboc

#endif
