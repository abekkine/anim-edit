#ifndef WORLD_POSITION_EVENT_H_
#define WORLD_POSITION_EVENT_H_

#include "EventInterface.h"

class WorldPositionEvent : public EventInterface {
public:
    WorldPositionEvent(double x, double y) :
        x_(x), y_(y) {}
    ~WorldPositionEvent() {}
    void GetPosition(double& x, double& y) {
        x = x_;
        y = y_;
    }
private:
    double x_;
    double y_;
};

#endif  // WORLD_POSITION_EVENT_H_

