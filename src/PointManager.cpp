#include "PointManager.h"

PointManager::PointManager() {}

PointManager::~PointManager() {}

Point* PointManager::AddPoint(int frame, double x, double y) {
	Point* p = new Point(frame, x, y);

	point_list_.push_back(p);

	return p;
}

std::vector<Point*> PointManager::GetPointsNearOf(int frame, double x, double y, bool save, double vicinity) {

	std::vector<Point*> points;

	for (auto point : point_list_) {
		if (! save) {
			point->Select(Point::NONE);
		}
		if (point->frame_number_ == frame) {
			double dx = x - point->x_;
			double dy = y - point->y_;
			if ((dx*dx + dy*dy)<vicinity) {
				point->Select(Point::SELECT);
				points.push_back(point);
			}
		}
	}

	return points;
}
