#ifndef CURSOR_EVENT_H_
#define CURSOR_EVENT_H_

#include "EventInterface.h"

class CursorEvent : public EventInterface {
public:
    CursorEvent(double x, double y) :
        x_(x), y_(y) {}
    ~CursorEvent() {}
    void GetCursor(double& x, double& y) {
        x = x_;
        y = y_;
    }
private:
    double x_;
    double y_;
};

#endif  // CURSOR_EVENT_H_

