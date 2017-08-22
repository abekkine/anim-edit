#include "Point.h"

int Point::num_ = 0;

Point::Point(int frame, double x, double y)
: frame_number_(frame), selected_(NONE), x_(x), y_(y) {
	num_++;
	id_=num_;
}

Point::~Point() {}

void Point::Select(SelectType value) {
	selected_ = value;
}
