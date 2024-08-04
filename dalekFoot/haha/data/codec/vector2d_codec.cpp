#include "data/codec/vector2d_codec.h"

namespace cooboc {
namespace data {
proto::Vector2D convert(const data::Vector2D &in) {
    proto::Vector2D out;
    out.set_x(in.x);
    out.set_y(in.y);
    return out;
}
}    // namespace data
}    // namespace cooboc