#ifndef __INTENTS_COMMON_PARAMETERS_H__
#define __INTENTS_COMMON_PARAMETERS_H__

namespace cooboc {
namespace intents {

void setupParameters();

struct Parameters {
    bool encoderDirection[4U];
    bool motorDirection[6U];
};

extern Parameters parameters;
}    // namespace intents
}    // namespace cooboc

#endif
