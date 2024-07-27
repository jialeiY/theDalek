#include <mcap/writer.hpp>
#include <chrono>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <gen/test.pb.h>

#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>

// Returns the system time in nanoseconds. std::chrono is used here, but any
// high resolution clock API (such as clock_gettime) can be used.
mcap::Timestamp now()
{
    return mcap::Timestamp(std::chrono::duration_cast<std::chrono::nanoseconds>(
                               std::chrono::system_clock::now().time_since_epoch())
                               .count());
}

int main_ros()
{
    mcap::McapWriter writer;
    mcap::Status status = writer.open("runtime/output.mcap", mcap::McapWriterOptions("testNdoe"));
    if (!status.ok())
    {
        // ERROR
        return -1;
    }
    // Register a Schema
    mcap::Schema stdMsgsString("std_msgs/String", "ros2msg", "string data");
    writer.addSchema(stdMsgsString);

    // Register a channel
    mcap::Channel chatterPublisher("/topic", "cdr", stdMsgsString.id);
    writer.addChannel(chatterPublisher);

    // Write our message
    for (int i = 0; i < 100; ++i)
    {
        mcap::Message msg;
        msg.channelId = chatterPublisher.id;
        msg.sequence = i;              // Optional
        msg.logTime = now();           // Required nanosecond timestamp
        msg.publishTime = msg.logTime; // Set to logTime if not available

        // Create a message payload. This would typically be done by your own
        // serialization library. In this example, we manually create ROS1 binary data
        std::array<std::byte, 4 + 50> payload;
        std::string content = std::string("hello from ") + std::to_string(i);

        const uint32_t length = content.size();

        std::memcpy(payload.data(), &length, 4);
        std::memcpy(payload.data() + 4, content.c_str(), length);

        msg.data = payload.data();
        msg.dataSize = payload.size();
        std::ignore = writer.write(msg);

        usleep(10000ULL);
    }

    writer.close();
    return 0;
}

// Recursively adds all `fd` dependencies to `fd_set`.
void fdSetInternal(google::protobuf::FileDescriptorSet &fd_set,
                   std::unordered_set<std::string> &files,
                   const google::protobuf::FileDescriptor *fd)
{
    for (int i = 0; i < fd->dependency_count(); ++i)
    {
        const auto *dep = fd->dependency(i);
        auto [_, inserted] = files.insert(dep->name());
        if (!inserted)
            continue;
        fdSetInternal(fd_set, files, fd->dependency(i));
    }
    fd->CopyTo(fd_set.add_file());
}

// Returns a serialized google::protobuf::FileDescriptorSet containing
// the necessary google::protobuf::FileDescriptor's to describe d.
std::string fdSet(const google::protobuf::Descriptor *d)
{
    std::string res;
    std::unordered_set<std::string> files;
    google::protobuf::FileDescriptorSet fd_set;
    fdSetInternal(fd_set, files, d->file());
    return fd_set.SerializeAsString();
}

mcap::Schema createSchema(const google::protobuf::Descriptor *d)
{
    mcap::Schema schema(d->full_name(), "protobuf", fdSet(d));
    return schema;
}

int main()
{
    mcap::McapWriter writer;
    auto s = writer.open("runtime/output.mcap", mcap::McapWriterOptions("testnode"));
    if (!s.ok())
    {
        return -1;
    }

    // Create a schema for the foxglove.PosesInFrame message.
    mcap::Schema path_schema = createSchema(cooboc::data::Test::descriptor());
    writer.addSchema(path_schema); // Assigned schema id is written to path_schema.id
    // Register Channel
    mcap::Channel path_channel("/planner/path", "protobuf", path_schema.id);
    writer.addChannel(path_channel); // Assigned channel id written to path_channel.id

    for (int i = 0; i < 100; ++i)
    {
        cooboc::data::Test testMessage;
        testMessage.set_id(i);

        std::string data = testMessage.SerializeAsString();

        mcap::Message msg;
        msg.channelId = path_channel.id;
        uint64_t timestamp_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                                    std::chrono::system_clock::now().time_since_epoch())
                                    .count();
        msg.logTime = timestamp_ns;
        msg.publishTime = msg.logTime;
        msg.data = reinterpret_cast<const std::byte *>(data.data());
        msg.dataSize = data.size();

        std::ignore = writer.write(msg);
        // cooboc::data::Test
        usleep(10000ULL);
    }
    writer.close();
    return 0;
}