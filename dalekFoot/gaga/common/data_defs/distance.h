
#ifndef __COMMON_DATA_DEFS_DISTANCE_H__
#define __COMMON_DATA_DEFS_DISTANCE_H__


#include <cstdint>
#include "common/data_defs/duration.h"

namespace cooboc {
namespace data {

struct Distance {
    float value {0.0F};    // m

    // TODO, make speed
    float operator/(const Duration &duration) const {
        return value / duration.seconds();
    }
};

}    // namespace data
}    // namespace cooboc

#endif