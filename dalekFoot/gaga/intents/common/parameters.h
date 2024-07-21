#ifndef __INTENTS_COMMON_PARAMETERS_H__
#define __INTENTS_COMMON_PARAMETERS_H__

namespace cooboc {
namespace intents {

namespace parameters {
constexpr bool kEncoderDirection[4U] {false, false, true, true};
constexpr bool kMotorDirection[6U] {true, false, false, true, false, false};

}    // namespace parameters
}    // namespace intents
}    // namespace cooboc

#endif
