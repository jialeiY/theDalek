#ifndef __INTENTS_DEBUG_WRITER_INTENT_MCAP_HELPER_H__
#define __INTENTS_DEBUG_WRITER_INTENT_MCAP_HELPER_H__

#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <mcap/writer.hpp>

namespace cooboc {
namespace intent {
namespace mcap_helper {


// Recursively adds all `fd` dependencies to `fd_set`.
void fdSetInternal(google::protobuf::FileDescriptorSet &fd_set,
                   std::unordered_set<std::string> &files,
                   const google::protobuf::FileDescriptor *fd);

// Returns a serialized google::protobuf::FileDescriptorSet containing
// the necessary google::protobuf::FileDescriptor's to describe d.
std::string fdSet(const google::protobuf::Descriptor *d);

mcap::Schema createSchema(const google::protobuf::Descriptor *d);
}    // namespace mcap_helper
}    // namespace intent
}    // namespace cooboc

#endif
