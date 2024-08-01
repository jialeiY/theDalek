#ifndef __INTENTS_ODOMETRY_INTENT_ODOMETRY_INTENT_H__
#define __INTENTS_ODOMETRY_INTENT_ODOMETRY_INTENT_H__

#include "intents/intent_base.h"

namespace cooboc {
namespace intent {
class OdometryIntent : public IntentBase {
  public:
    OdometryIntent();
    virtual ~OdometryIntent();
    virtual void setup() override;
    virtual void tick() override;
};
}    // namespace intent
}    // namespace cooboc

#endif
