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
	Point(int parent, double x, double y);
	~Point();
	void Select(SelectType value);
public:
	int parent_;
	int id_;
	SelectType selected_;
	double x_;
	double y_;
private:
	static int num_;
};

#endif  // POINT_H_
