#ifndef __INTENTS_TRAJECTORY_INTENT_TRAJECTORY_INTENT_H__
#define __INTENTS_TRAJECTORY_INTENT_TRAJECTORY_INTENT_H__


#include <array>
#include <optional>
#include <vector>
#include "data/defs/passing_point.h"
#include "data/defs/static_vector.h"
#include "intents/intent_base.h"
#include "intents/topics/topics.h"

namespace cooboc {
namespace intent {

namespace detail {

using RouteSegmentLengthArray = std::array<float, RouteTopic::kPolylineCapacity>;

using PassingPointList =
  data::StaticVector<data::PassingPoint, TrajectoryTopic::kPassingPointCapacity>;
// using PassingPointList        = std::vector<data::PassingPoint>;

float calculateApproximateRouteLength(RouteSegmentLengthArray &routeSegmentLengthArray);

// TODO: move these functions to TrajectoryIntent
TrajectoryId generateTrajectoryId();
void generateTrajectoriesBasedOnRoutes(const RouteTopic &routeTopic,
                                       TrajectoryTopic &trajectoryTopic);


/**
 * Generate one trajectory segment based on the given information
 * The first point is excluded, the end point is included
 *
 * @param startPoint [in]: the start point of a route segment
 * @param startPointOrientationOpt [in]: The slope on the start point
 * @param endPoint [in]: the end point of a route segment
 * @param nextSegmentOrientationOpt [in]: The slope on the start point of next segment
 * @param curvatureDistribution [in]: How the curvature generated
 * @param maximumPointNumber [in]: The number of points that want generated a most
 * @param passingPointList [out]: passing point of a trajectory
 * @return the last orientation of the trajectory
 */
std::optional<float> makeTrajectory(const data::Position2D &startPoint,
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

// Generate point without endpoint
void makeQuadraticBezierCurve(const data::Position2D &pa,
                              const data::Position2D &pb,
                              const data::Position2D &pc,
                              const data::Position2D &pd,
                              const std::size_t count,
                              PassingPointList &passingPointList);

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
