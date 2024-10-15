#ifndef __DATA_DEFS_STATIC_POLYLINE_H__
#define __DATA_DEFS_STATIC_POLYLINE_H__

#include <cstdint>
#include "data/defs/position2d.h"

namespace cooboc {
namespace data {

template<std::size_t N>
class StaticPolyline {
  public:
    StaticPolyline() : size_ {0U} {
        for (std::size_t i {0U}; i < N; ++i) {
            points_[i] = data::Position2D {0.0F, 0.0F};
        }
    }
    void reset() {
        size_ = 0U;
        for (std::size_t i {0U}; i < N; ++i) {
            points_[i] = data::Position2D {0.0F, 0.0F};
        }
    }

    void insert(const data::Position2D &point) {
        points_[size_] = point;
        size_++;
    }

    inline std::size_t size() const {
        return size_;
    }
    inline std::size_t capacity() const {
        return N;
    }
    inline const data::Position2D &pointAt(std::size_t i) const {
        return points_[i];
    }

  private:
    std::size_t size_ {0U};
    data::Position2D points_[N] {};
};
}    // namespace data
}    // namespace cooboc

#endif
