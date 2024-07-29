#include "data/codec/position2d_codec.h"

namespace cooboc {
namespace data {
proto::Position2D convert(const data::Position2D &in) {
    proto::Position2D out;
    out.set_x(in.x);
    out.set_y(in.y);
    return out;
}
}    // namespace data
}    // namespace cooboc