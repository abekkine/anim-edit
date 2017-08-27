#ifndef POINT_MANAGER_H_
#define POINT_MANAGER_H_

#include <vector>
#include <memory>

#include "Point.h"
#include "AnimComponent.h"

class PointManager {
public:
    static PointManager& Instance() {
        static PointManager instance_;
        return instance_;
    }
public:
	std::shared_ptr<Point> Add(int parent, double x, double y);
	void Delete(int id);
private:
	PointManager();
	~PointManager();
private:
	std::vector<std::shared_ptr<Point>> point_list_;
};

#define POINTS PointManager::Instance()

#endif  // POINT_MANAGER_H_
