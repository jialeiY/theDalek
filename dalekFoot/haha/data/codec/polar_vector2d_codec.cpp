#include "data/codec/polar_vector2d_codec.h"

namespace cooboc {
namespace data {
proto::PolarVector2D convert(const data::PolarVector2D &in) {
    proto::PolarVector2D out;
    out.set_orientation(in.orientation);
    out.set_value(in.value);
    return out;
}

}    // namespace data
}    // namespace cooboc