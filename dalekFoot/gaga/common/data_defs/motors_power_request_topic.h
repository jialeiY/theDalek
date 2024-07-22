#ifndef __COMMON_DATA_DEFS_SPI_COMM_POD_H__
#define __COMMON_DATA_DEFS_SPI_COMM_POD_H__

#include <cstdint>


namespace cooboc {
namespace data {


struct MotorPowerRequest {
    std::int8_t power;
};

struct MotorsPowerRequestTopic {
    MotorPowerRequest request[4];
};


}    // namespace data

}    // namespace cooboc


#endif
