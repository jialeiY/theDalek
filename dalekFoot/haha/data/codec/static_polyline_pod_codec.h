#ifndef __DATA_CODEC_STATIC_POLYLINE_POD_CODEC_H__
#define __DATA_CODEC_STATIC_POLYLINE_POD_CODEC_H__

#include <cstdint>
#include "data/codec/vector2d_codec.h"
#include "data/defs/static_polyline_pod.h"
#include "gen/data/proto/static_polyline_pod.pb.h"

namespace cooboc {
namespace data {

template<std::size_t N>
proto::StaticPolylinePod convert(const data::StaticPolylinePod<N> &in) {
    proto::StaticPolylinePod out;
    out.set_capacity(N);
    out.set_size(in.size);

    for (std::size_t i {0U}; i < N; ++i) {
        proto::Vector2D *vertex = out.add_points();
        *vertex                 = convert(in.at(i));
    }
    return out;
}

}    // namespace data
}    // namespace cooboc
#endif
