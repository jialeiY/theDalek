#ifndef __INTENTS_COMMON_PUB_SUB_STUB_H__
#define __INTENTS_COMMON_PUB_SUB_STUB_H__

namespace cooboc {
namespace intents {
class PubSubStub {
  public:
    template<typename Topic>
    void registerTopic() {
        new Topic();
    };
};
}    // namespace intents
}    // namespace cooboc

#endif
