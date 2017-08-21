#ifndef QUIT_EVENT_H_
#define QUIT_EVENT_H_

#include "EventInterface.h"

class QuitEvent : public EventInterface {
public:
    QuitEvent() {}
    ~QuitEvent() {} 
};

#endif  // QUIT_EVENT_H_

