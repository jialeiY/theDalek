#ifndef __DATA_DEFS_REFERENCE_PATH_ID_H__
#define __DATA_DEFS_REFERENCE_PATH_ID_H__

#include <cstdint>

namespace cooboc {
namespace data {

using ReferencePathId = std::uint64_t;
constexpr ReferencePathId kInvalidReferencePathId {0U};


}    // namespace data
}    // namespace cooboc


#endif
