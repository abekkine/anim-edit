#include "PointManager.h"

PointManager::PointManager() {}

PointManager::~PointManager() {}

Point* PointManager::Add(int parent, int frame, double x, double y) {
	Point* p = new Point(parent, frame, x, y);

	point_list_.push_back(p);

	return p;
}

void PointManager::Delete(Point* p) {

	p->id_ = -1;
}

std::vector<Point*> PointManager::GetPointsNearOf(int frame, double x, double y, double vicinity) {

	std::vector<Point*> points;

	for (auto iP=point_list_.begin(); iP!=point_list_.end();) {
		if (-1 == (*iP)->id_) {
			point_list_.erase(iP);
			delete (*iP);
		}
		else {
			++iP;
		}
	}

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

