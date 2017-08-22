#include "PointManager.h"

PointManager::PointManager() {}

PointManager::~PointManager() {}

Point* PointManager::AddPoint(int frame, double x, double y) {
	Point* p = new Point(frame, x, y);

	point_list_.push_back(p);

	return p;
}

std::vector<Point*> PointManager::GetPointsNearOf(int frame, double x, double y, double vicinity) {

	std::vector<Point*> points;

	for (auto point : point_list_) {
		if (point->frame_number_ == frame) {
			double dx = x - point->x_;
			double dy = y - point->y_;
			if ((dx*dx + dy*dy)<vicinity) {
				if (point->selected_ == Point::NONE) {
					point->Select(Point::SELECT);
				}
				points.push_back(point);
			}
			else {
				point->Select(Point::NONE);
			}
		}
		else {
			point->Select(Point::NONE);
		}
	}

	return points;
}

