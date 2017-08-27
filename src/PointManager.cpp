#include "PointManager.h"

PointManager::PointManager() {}

PointManager::~PointManager() {}

std::shared_ptr<Point> PointManager::Add(int parent, double x, double y) {

	auto p = std::make_shared<Point>(parent, x, y);

	point_list_.push_back(p);

	return p;
}

void PointManager::Delete(int id) {
	for (auto iP=point_list_.begin(); iP!=point_list_.end();) {
		if ( (*iP)->id_ == id) {
			point_list_.erase(iP);
		}
		else {
			++iP;
		}
	}
}
