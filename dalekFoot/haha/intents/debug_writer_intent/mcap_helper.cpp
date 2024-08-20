#define MCAP_IMPLEMENTATION

#include "intents/debug_writer_intent/mcap_helper.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <mcap/writer.hpp>

namespace cooboc {
namespace intent {
namespace mcap_helper {


// Recursively adds all `fd` dependencies to `fd_set`.
void fdSetInternal(google::protobuf::FileDescriptorSet &fd_set,
                   std::unordered_set<std::string> &files,
                   const google::protobuf::FileDescriptor *fd) {
    for (int i = 0; i < fd->dependency_count(); ++i) {
        const auto *dep    = fd->dependency(i);
        auto [_, inserted] = files.insert(dep->name());
        if (!inserted)
            continue;
        fdSetInternal(fd_set, files, fd->dependency(i));
    }
    fd->CopyTo(fd_set.add_file());
}

// Returns a serialized google::protobuf::FileDescriptorSet containing
// the necessary google::protobuf::FileDescriptor's to describe d.
std::string fdSet(const google::protobuf::Descriptor *d) {
    std::string res;
    std::unordered_set<std::string> files;
    google::protobuf::FileDescriptorSet fd_set;
    fdSetInternal(fd_set, files, d->file());
    return fd_set.SerializeAsString();
}

mcap::Schema createSchema(const google::protobuf::Descriptor *d) {
    mcap::Schema schema(d->full_name(), "protobuf", fdSet(d));
    return schema;
}
}    // namespace mcap_helper
}    // namespace intent
}    // namespace cooboc