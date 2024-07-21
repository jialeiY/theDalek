#ifndef __INTENTS_COMMON_DATA_POOL_H__
#define __INTENTS_COMMON_DATA_POOL_H__

#include "intents/common/data_defs/encoder_reading_output.h"

namespace cooboc {
namespace data {


/**
 * Output:  EncoderReadingIntent
 * Input:   DebugDataIntent
 *          -- Next Cycle --
 *
 */

extern data::EncoderReadingOutput encoderReadingOutput;


}    // namespace data
}    // namespace cooboc

#endif
