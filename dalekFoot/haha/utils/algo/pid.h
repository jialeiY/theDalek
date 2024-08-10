#ifndef __UTILS_ALGO_PID_H__
#define __UTILS_ALGO_PID_H__

namespace cooboc {
namespace algo {
template<typename T>
class PID {
  public:
    PID() : kp_ {}, ki_ {}, kd_ {}, lastError_ {}, output_ {} {};
    PID(const T kp, const T ki, const T kd) : kp_ {kp}, ki_ {ki}, kd_ {kd} {};
    ~PID() {};

    void updatePID(const T kp, const T ki, const T kd) {
        kp_ = kp;
        ki_ = ki;
        kd_ = kd;
    }

    void updateError(T e) {
        //
        const float errorDiff = e - lastError_;
        output_               = (kp_ * e) + (kd_ * errorDiff);

        lastError_ = e;
    }

    float getOutput() const { return output_; }
    void reset() {
        lastError_ = T {};
        output_    = T {};
    };


  private:
    T kp_ {};
    T ki_ {};
    T kd_ {};

    T lastError_ {};
    T output_ {};
};
}    // namespace algo
}    // namespace cooboc

#endif
