#ifndef __COMM_DATA_GH_PROTOCOL_H__
#define __COMM_DATA_GH_PROTOCOL_H__

#include <cstdint>


namespace cooboc {
namespace comm {

struct GHProtocol {
    char a;
    uint64_t b;

} __attribute__((packed));


}    // namespace comm
}    // namespace cooboc


#endif
