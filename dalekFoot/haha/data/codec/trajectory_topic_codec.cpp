#include "data/codec/trajectory_topic_codec.h"
#include <cstdint>
#include "data/codec/passing_point_codec.h"
#include "gen/data/proto/passing_point.pb.h"
#include "intents/topics/common.h"

namespace cooboc {
namespace data {

proto::TrajectoryTopic convert(const intent::TrajectoryTopic &in) {
    proto::TrajectoryTopic out;
    out.set_hasvalue(in.hasValue);
    out.set_trajectoryid(in.trajectoryId);
    out.set_passingpointsize(in.passingPointSize);

    for (std::size_t i {0U}; i < intent::kTrajectoryPassingPointCapacity; ++i) {
        proto::PassingPoint *passingPoint = out.add_passingpoint();
        *passingPoint                     = convert(in.passingPoint[i]);
    }
    out.set_routeid(in.routeId);

    return out;
}

}    // namespace data
}    // namespace cooboc