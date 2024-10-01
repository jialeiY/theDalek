#ifndef __INTENTS_REFERENCE_PATH_INTENT_COMPONENTS_SAMPLING_H__
#define __INTENTS_REFERENCE_PATH_INTENT_COMPONENTS_SAMPLING_H__

#include <array>
#include <optional>
#include "data/defs/position2d.h"
#include "data/defs/route_segment.h"
#include "data/defs/static_vector.h"
#include "intents/topics/common.h"
#include "intents/topics/reference_path_topic.h"

namespace cooboc {
namespace intent {
namespace reference_path {


using PassingPointList = data::StaticVector<data::Position2D, kReferencePathPassingPointCapacity>;
using PassingPointsSegment = std::array<data::PolarVector2D, kReferencePathPassingPointCapacity>;

/**
 * Generate passing point list based on route information
 * @param startPoint [in]: the start point of route
 * @param routeSegment [in]: the list describe route
 * @param routeSegmentSize [in]: the size of list of route
 * @param passingPointList [out]: the passing point of trajectory
 * @return void
 */
void generatePassingPointListBasedOnRoute(const data::Position2D &startPoint,
                                          const data::RouteSegment *routeSegment,
                                          const std::size_t routeSegmentSize,
                                          PassingPointList &passingPointList);

/**
 * Calculate each trajectory segment's vector
 * @param passingPointList [in]: the trajectory passing point list
 * @param passingPointsOrientation [out]: the polar vector of each segment
 * @return void
 */
void calculatePassingPointsSegment(const PassingPointList &passingPointList,
                                   PassingPointsSegment &passingPointsSegment);

namespace detail {

// using RouteSegmentLengthArray = std::array<float, RouteTopic::kPolylineCapacity>;
// /**
//  * Calculate the approximate length of routeTopic
//  * @param routeTopic [in]: the route
//  * @param routeSegmentLengthArray [out]: each length of the route segment
//  * @return the total length of all route segments
//  */
// float calculateApproximateRouteLength(const RouteTopic &routeTopic,
//                                       RouteSegmentLengthArray &routeSegmentLengthArray);


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
std::optional<float> makePassingPoints(const data::Position2D &startPoint,
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
}    // namespace reference_path
}    // namespace intent
}    // namespace cooboc


#endif
