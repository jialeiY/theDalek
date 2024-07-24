#ifndef __COMMON_DATA_DEFS_TIMEPOINT_H__
#define __COMMON_DATA_DEFS_TIMEPOINT_H__
#include <cstdint>
#include "common/data_defs/duration.h"

namespace cooboc {
namespace data {

struct Timepoint {
    // 0,0 is a magic number that indicate the timestamp is not initialized
    explicit Timepoint() : systick_ {0U}, systickVal_ {0U} {}
    explicit Timepoint(const std::uint32_t systick,
                       const std::uint32_t systickVal) :
        systick_ {systick},
        systickVal_ {180000U - systickVal} {}
    Timepoint(const Timepoint &another) :
        systick_ {another.systick_},
        systickVal_ {another.systickVal_} {}
    explicit Timepoint(const Timepoint &&another) :
        systick_ {another.systick_},
        systickVal_ {another.systickVal_} {}
    void operator=(const Timepoint &another) {
        systick_    = another.systick_;
        systickVal_ = another.systickVal_;
    }
    void operator=(const Timepoint &&another) {
        systick_    = another.systick_;
        systickVal_ = another.systickVal_;
    }

    bool operator==(const Timepoint t2) const {
        return (systick_ == t2.systick_) && (systickVal_ == t2.systickVal_);
    }

    bool operator<(const Timepoint t2) const {
        if (systick_ < t2.systick_)
            return true;
        if (systick_ > t2.systick_)
            return false;
        return systickVal_ < t2.systickVal_;
    }

    Duration operator-(const data::Timepoint &another) const {
        data::Timepoint tGreat;
        data::Timepoint tLess;
        bool isNagative = false;

        if (*this < another) {
            isNagative = true;
            tGreat     = another;
            tLess      = *this;
        } else {
            isNagative = false;
            tGreat     = *this;
            tLess      = another;
        }


        if (tGreat.systickVal_ < tLess.systickVal_) {
            // need to carry
            return Duration {
              isNagative,
              (tGreat.systick_ - tLess.systick_ - 1U),
              (tGreat.systickVal_ + 180000U - tLess.systickVal_)};
        } else {
            return Duration {isNagative,
                             (tGreat.systick_ - tLess.systick_),
                             (tGreat.systickVal_ - tLess.systickVal_)};
        }
    }

    std::uint32_t milliseconds() const { return systick_; }

  private:
    std::uint32_t systick_ {0U};
    std::uint32_t systickVal_ {0U};
};


}    // namespace data
}    // namespace cooboc

#endif
