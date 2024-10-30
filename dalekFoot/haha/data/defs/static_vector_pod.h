#ifndef __DATA_DEFS_STATIC_VECTOR_POD_H__
#define __DATA_DEFS_STATIC_VECTOR_POD_H__

#include <cstdint>

namespace cooboc {
namespace data {

template<typename T, std::size_t N>
struct StaticVectorPod {
    T data[N] {};
    std::size_t size {0U};

    static constexpr std::size_t capacity() {
        return N;
    }

    std::size_t length() const {
        return size;
    }

    void emplace_back(T&& value) {
        if (size < N) {
            data[size] = value;
            size++;
        }
    }

    void push_back(const T& value) {
        if (size < N) {
            data[size] = value;
            size++;
        }
    }

    void push_back(T&& value) {
        emplace_back(std::move(value));
    }

    const T& back() {
        return data[size - 1U];
    }
    const T& back() const {
        return data[size - 1U];
    }
    const T& operator[](const std::size_t i) {
        return data[i];
    }
    const T& operator[](const std::size_t i) const {
        return data[i];
    }
    const T& at(const std::size_t i) {
        return data[i];
    }
    const T& at(const std::size_t i) const {
        return data[i];
    }

    void reset() {
        size = 0U;
    }

    void reverse() {
        if (size > 0U) {
            std::size_t first = 0U;
            std::size_t last  = size - 1U;
            while (first < last) {
                T temp      = std::move(data[first]);
                data[first] = std::move(data[last]);
                data[last]  = std::move(temp);
                first++;
                last--;
            }
        }
    }
};

}    // namespace data
}    // namespace cooboc


#endif
