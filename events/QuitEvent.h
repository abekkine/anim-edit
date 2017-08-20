#ifndef QUIT_EVENT_H_
#define QUIT_EVENT_H_

#include "EventInterface.h"

class QuitEvent : public EventInterface {
public:
    QuitEvent() {}
    ~QuitEvent() {} 
    void dummy() {}
};

#endif  // QUIT_EVENT_H_

