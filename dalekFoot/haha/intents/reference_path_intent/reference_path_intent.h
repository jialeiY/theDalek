#ifndef __INTENTS_REFERENCE_PATH_INTENT_REFERENCE_PATH_INTENT_H__
#define __INTENTS_REFERENCE_PATH_INTENT_REFERENCE_PATH_INTENT_H__


#include <array>
#include <optional>
#include <vector>
#include "data/defs/passing_point.h"
#include "data/defs/static_vector.h"
#include "intents/intent_base.h"
#include "intents/reference_path_intent/components/sampling.h"
#include "intents/topics/topics.h"

namespace cooboc {
namespace intent {

// ReferencePathIntent take the Route from RouteIntent and make a trajectory that vehicle can follow
class ReferencePathIntent : public IntentBase {
  public:
    // ReferencePathIntent take the Route from RouteIntent and make a trajectory that vehicle can
    // follow
    ReferencePathIntent();
    virtual ~ReferencePathIntent();
    virtual void setup() override;
    virtual void tick() override;

  private:
    reference_path::PassingPointList passingPointList_ {};
    reference_path::PassingPointsSegment passingPointsSegment_ {};
    ReferencePathId referencePathId_ {0U};

    void outputTopic();
    ReferencePathId makeNewReferencePathId();
};


}    // namespace intent
}    // namespace cooboc

#endif
