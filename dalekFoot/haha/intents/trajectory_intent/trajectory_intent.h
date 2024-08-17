#ifndef __INTENTS_TRAJECTORY_INTENT_TRAJECTORY_INTENT_H__
#define __INTENTS_TRAJECTORY_INTENT_TRAJECTORY_INTENT_H__


#include <array>
#include <optional>
#include <vector>
#include "intents/intent_base.h"
#include "intents/topics/topics.h"

namespace cooboc {
namespace intent {

namespace detail {

using RouteSegmentLengthArray = std::array<float, RouteTopic::kPolylineCapacity>;
using PassingPointList        = std::vector<PassingPoint>;

float calculateApproximateRouteLength(RouteSegmentLengthArray &routeSegmentLengthArray);

// TODO: move these functions to TrajectoryIntent
TrajectoryId generateTrajectoryId();
void generateTrajectoriesBasedOnRoutes(const RouteTopic &routeTopic,
                                       TrajectoryTopic &trajectoryTopic);

float makeTrajectory(const data::Position2D &startPoint,
                     const std::optional<float> &startPointOrientationOpt,
                     const data::Position2D &endPoint,
                     std::optional<float> &nextSegmentOrientationOpt,
                     const data::CurvatureDistribution &curvatureDistribution,
                     const std::size_t maximumPointNumber,
                     PassingPointList &passingPointList);

// Generate point without endpoint
void makeCubicBezierCurve(const data::Position2D &pa,
                          const data::Position2D &pb,
                          const data::Position2D &pc,
                          const std::size_t count,
                          PassingPointList &pointList);

}    // namespace detail


// TrajectoryIntent take the Route from RouteIntent and make a trajectory that vehicle can follow
class TrajectoryIntent : public IntentBase {
  public:
    // TrajectoryIntent take the Route from RouteIntent and make a trajectory that vehicle can
    // follow
    TrajectoryIntent();
    virtual ~TrajectoryIntent();
    virtual void setup() override;
    virtual void tick() override;
};


}    // namespace intent
}    // namespace cooboc

#endif
