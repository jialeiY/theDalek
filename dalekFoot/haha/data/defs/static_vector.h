#ifndef __DATA_DEFS_STATIC_VECTOR_H__
#define __DATA_DEFS_STATIC_VECTOR_H__

#include <cstdint>

namespace cooboc {
namespace data {

template<typename T, std::size_t N>
class StaticVector {
  public:
    explicit StaticVector() {
        dataPtr_ = new T[N];
        size_    = 0U;
    }
    explicit StaticVector(T* dataPtr) : dataPtr_ {dataPtr}, size_ {0U} {}
    explicit StaticVector(const StaticVector&)   = delete;
    StaticVector& operator=(const StaticVector&) = delete;

    std::size_t size() const { return size_; }
    explicit StaticVector(StaticVector<T, N>&& b) {
        dataPtr_ = b.dataPtr_;
        size_    = b.size_;
    }

    void emplace_back(T&& data) {
        if (size_ < N) {
            dataPtr_[size_] = data;
            size_++;
        }
    }

    void push_back(const T& data) {
        if (size_ < N) {
            dataPtr_[size_] = data;
            size_++;
        }
    }

    void push_back(T&& data) { emplace_back(std::move(data)); }
    const T& back() { return dataPtr_[size_ - 1U]; }
    const T& operator[](const std::size_t i) { return dataPtr_[i]; }
    const T& operator[](const std::size_t i) const { return dataPtr_[i]; }

    void reset() { size_ = 0U; }

  private:
    T* dataPtr_;
    std::size_t size_;
};

}    // namespace data
}    // namespace cooboc


#endif
