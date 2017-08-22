#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	enum SelectType {
		NONE,
		SELECT,
		MARK
	};
public:
	Point(int frame, double x, double y);
	~Point();
	void Select(SelectType value);
public:
	int frame_number_;
	SelectType selected_;
	double x_;
	double y_;
};

#endif  // POINT_H_
