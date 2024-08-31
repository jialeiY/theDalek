#include "intents/motion_planning_intent/components/profile.h"
#include <cmath>
#include <cstdio>
#include <tuple>
#include "utils/math.h"

namespace cooboc {
namespace intent {
namespace motion_planning {

namespace detail {
float calculateResidualValue(const float angle, const float coefficient) {
    const float y = 1.0F / ((angle * angle) + 1.0F);

    return ((y - 1.0F) * 2.0F * (1.0F - coefficient)) + 1.0F;
}

}    // namespace detail

void calculateCurvatureProfile(const data::PassingPoint *passingPoint,
                               const std::size_t &passingPointSize,
                               CurvatureProfile &curvatureProfile) {
    curvatureProfile.push_back(std::make_tuple<float, float>(0.0F, 0.0F));

    float lastOrientation = passingPoint[1U].segment.orientation;
    float totalLength     = passingPoint[1U].segment.value;

    for (std::size_t i {2U}; i < passingPointSize; ++i) {
        const data::PolarVector2D &segment {passingPoint[i].segment};
        const float diffOrientation = segment.orientation - lastOrientation;
        float curvature             = std::fmod(diffOrientation, 2.0F * utils::math::PI);
        if (curvature > utils::math::PI) {
            curvature -= 2.0F * utils::math::PI;
        }
        if (curvature < -utils::math::PI) {
            curvature += 2.0F * utils::math::PI;
        }
        curvatureProfile.push_back(std::make_tuple(totalLength, curvature));

        totalLength += segment.value;
        lastOrientation = segment.orientation;
    }
    curvatureProfile.push_back(std::make_tuple(totalLength, 0.0F));
}

void calculateMotionProfile(const CurvatureProfile &curvatureProfile,
                            const float maximumAcceleration,
                            const float maximumVelocity,
                            MotionProfile &motionProfile) {
    constexpr float kMaximumAccelerationLongitudinalResidual {0.1};
    constexpr float kMaximumVelocityLongitudinalResidual {0.1};

    motionProfile.reset();
    if (curvatureProfile.size() < 3U) {
        for (std::size_t i {0}; i < curvatureProfile.size(); ++i) {
            motionProfile.push_back(std::make_tuple(maximumVelocity, maximumAcceleration));
        }
        return;
    }

    float lastVelocity = maximumVelocity;

    // Put the result in reversed order
    motionProfile.push_back(std::make_tuple(lastVelocity, maximumAcceleration));
    float lastLength = std::get<0>(curvatureProfile.back());

    for (std::int32_t i {curvatureProfile.size() - 2U}; i > 0; --i) {
        const auto &curvaturePoint {curvatureProfile[i]};
        const float currentLength {std::get<0U>(curvaturePoint)};
        const float curvature {std::get<1U>(curvaturePoint)};

        const float travel = lastLength - currentLength;


        const float pointMaxVelocity =
          maximumVelocity *
          detail::calculateResidualValue(curvature, kMaximumVelocityLongitudinalResidual);
        const float pointMaxAcceleration =
          maximumAcceleration *
          detail::calculateResidualValue(curvature, kMaximumAccelerationLongitudinalResidual);


        const float vCurrentMax =
          std::sqrt(lastVelocity * lastVelocity + (2.0F * travel * pointMaxAcceleration));

        lastVelocity = std::min(std::min(vCurrentMax, pointMaxVelocity), maximumVelocity);
        lastLength   = currentLength;
        motionProfile.push_back(std::make_tuple(lastVelocity, pointMaxAcceleration));
    }
    // motionProfile.push_back(std::make_tuple(0.0F, 0.0F));
    motionProfile.reverse();

    std::printf("size of motion profile: %d\r\n", motionProfile.size());
}

}    // namespace motion_planning
}    // namespace intent
}    // namespace cooboc