#ifndef __INTENTS_INTENT_BASE_H__
#define __INTENTS_INTENT_BASE_H__


class IntentBase {
  public:
    IntentBase() {};
    virtual ~IntentBase() {};
    virtual void setup() = 0;
    virtual void tick()  = 0;

  private:
};

#endif
