#ifndef EDIT_EVENT_H_
#define EDIT_EVENT_H_

#include "EventInterface.h"

class EditEvent : public EventInterface {
public:
    enum EditEventType {
        NONE,
        TOGGLE
    };
public:
    EditEvent(EditEventType type) : type_(type) {}
    ~EditEvent() {}
    EditEventType GetType() const {
        return type_;
    }
private:
    EditEventType type_;
};

#endif  // EDIT_EVENT_H_

