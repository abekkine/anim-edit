#ifndef UI_DISPLAY_EVENT_H_
#define UI_DISPLAY_EVENT_H_

#include <string>

#include "EventInterface.h"

class UiDisplayEvent : public EventInterface {
public:
	UiDisplayEvent(std::string label, int x, int y, std::string message) 
	: label_(label), x_(x), y_(y), message_(message) {}
	~UiDisplayEvent() {}
	int X() { return x_; }
	int Y() { return y_; }
	const std::string& Message() { return message_; }
	const std::string& Label() { return label_; }
private:
	std::string label_;
	int x_;
	int y_;
	std::string message_;
};

#endif  // UI_DISPLAY_EVENT_H_
