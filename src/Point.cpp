#include "Point.h"

#include <iostream>

int Point::num_ = 0;

Point::Point(int parent, double x, double y)
: parent_(parent), selected_(NONE), x_(x), y_(y) {
	num_++;
	id_=num_;
}

Point::~Point() {
	std::cout << "~Point(" << id_ << ")" << std::endl;
}

void Point::Select(SelectType value) {
	selected_ = value;
}
