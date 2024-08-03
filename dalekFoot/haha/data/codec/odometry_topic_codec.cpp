#include "data/codec/odometry_topic_codec.h"
#include "data/codec/pose2d_codec.h"

namespace cooboc {
namespace data {
proto::OdometryTopic convert(const intent::OdometryTopic &in) {
    proto::OdometryTopic out;
    out.set_timestamp(in.timestamp);
    *out.mutable_pose() = convert(in.pose);
    return out;
}
}    // namespace data
}    // namespace cooboc
