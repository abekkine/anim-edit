#ifndef MOUSE_BUTTON_EVENT_H_
#define MOUSE_BUTTON_EVENT_H_

#include "EventInterface.h"

class MouseButtonEvent : public EventInterface {
public:
	enum EventType {
		NONE,
		LEFT_DOWN,
		LEFT_UP
	};
public:
	explicit MouseButtonEvent(EventType type) : type_(type) {}
	~MouseButtonEvent() {}
	EventType GetType() { return type_; }
private:
	EventType type_;
};

#endif  // MOUSE_BUTTON_EVENT_H_