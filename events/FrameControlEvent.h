#ifndef FRAME_CONTROL_EVENT_H_
#define FRAME_CONTROL_EVENT_H_

#include "EventInterface.h"

class FrameControlEvent : public EventInterface {
public:
    enum FrameEventType {
        NONE,
        ONION_SKIN,
        NEXT_FRAME,
        PREV_FRAME,
        FIRST_FRAME,
        LAST_FRAME
    };
public:
    explicit FrameControlEvent(FrameEventType type) : type_(type) {}
    ~FrameControlEvent() {}
    FrameEventType GetType() const {
        return type_;
    }
private:
    FrameEventType type_;
};

#endif  // FRAME_CONTROL_EVENT_H_

