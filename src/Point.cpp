#include "Point.h"

Point::Point(int frame, double x, double y)
: frame_number_(frame), selected_(NONE), x_(x), y_(y) {}

Point::~Point() {}

void Point::Select(SelectType value) {
	selected_ = value;
}
