#ifndef __INTENTS_REFERENCE_PATH_INTENT_REFERENCE_PATH_INTENT_H__
#define __INTENTS_REFERENCE_PATH_INTENT_REFERENCE_PATH_INTENT_H__

#include <array>
#include <optional>
#include <vector>
#include "data/defs/orientation.h"
#include "data/defs/passing_point.h"
#include "data/defs/reference_path_id.h"
#include "data/defs/static_vector.h"
#include "intents/intent_base.h"
#include "intents/reference_path_intent/components/sampling.h"
#include "intents/reference_path_intent/components/vertex_property.h"
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

  protected:
    intent::ReferencePathTopic referencePathTopic_ {};
    void resetCache();
    bool needUpdateReferencePath(const data::RouteId &routeId,
                                 const std::size_t &beginRouteIdx,
                                 const std::size_t &endRouteIdx) const;
    void makeReferencePath(const data::RouteId &routeId, const std::size_t beginIdx, const std::size_t endIdx);
    data::ReferencePathId makeReferencePathId() const;
    void makeSegmentByProfile(const std::vector<data::Position2D> &routeSegmentProfile,
                              ReferencePathTopic::Points &points,
                              size_t outputIndex) const;

    reference_path::RouteProfile routeProfile_;

    // reference_path::PassingPointList passingPointList_ {};
    // reference_path::PassingPointsSegment passingPointsSegment_ {};


    // void outputTopic();
    // data::ReferencePathId makeNewReferencePathId();
};


}    // namespace intent
}    // namespace cooboc

#endif
