#ifndef __COMMON_DATA_DEFS_CIRCULAR_BUFFER_H__
#define __COMMON_DATA_DEFS_CIRCULAR_BUFFER_H__

#include <cstdint>

namespace cooboc {
namespace data {

template<typename T, std::size_t N>
class CircularBuffer {
  public:
    CircularBuffer()          = default;
    virtual ~CircularBuffer() = default;

    void insert(const T& value) {
        sum -= data[idx];
        sum += value;
        data[idx] = value;
        idx++;
        idx %= N;
    }

    T getSum() const { return sum; }
    std::size_t capacity() const { return N; }

  private:
    T data[N];
    T sum {};
    std::size_t idx;
};

}    // namespace data
}    // namespace cooboc


#endif