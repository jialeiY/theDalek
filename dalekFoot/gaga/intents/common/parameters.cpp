#include "intents/common/parameters.h"

namespace cooboc {
namespace intents {

void setupParameters() {
    parameters = {
      .encoderDirection = {false, false, true, true},
      .motorDirection   = {true, false, false, true, false, false},
    };
}

Parameters parameters;

}    // namespace intents
}    // namespace cooboc
