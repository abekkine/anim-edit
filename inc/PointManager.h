#ifndef POINT_MANAGER_H_
#define POINT_MANAGER_H_

#include <vector>

#include "Point.h"

class PointManager {
public:
    static PointManager& Instance() {
        static PointManager instance_;
        return instance_;
    }
public:
	Point* Add(int parent, int frame, double x, double y);
	void Delete(Point* p);
	std::vector<Point*> GetPointsNearOf(int frame, double x, double y, double vicinity=25.0);
private:
	PointManager();
	~PointManager();
private:
	std::vector<Point*> point_list_;
	std::mutex point_mutex_;
};

#define POINTS PointManager::Instance()

#endif  // POINT_MANAGER_H_
