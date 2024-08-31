#include "intents/motion_planning_intent/components/profile.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {
namespace motion_planning {

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
        curvatureProfile.push_back(
          std::make_tuple<float, float>(std::move(totalLength), std::move(curvature)));

        totalLength += segment.value;
        lastOrientation = segment.orientation;
    }
    curvatureProfile.push_back(std::make_tuple<float, float>(std::move(totalLength), 0.0F));
}


}    // namespace motion_planning
}    // namespace intent
}    // namespace cooboc