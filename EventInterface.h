#ifndef EVENT_INTERFACE_H_
#define EVENT_INTERFACE_H_

class EventInterface {
public:
    virtual ~EventInterface() {}
    virtual int id() = 0;
};

#endif // EVENT_INTERFACE_H_

