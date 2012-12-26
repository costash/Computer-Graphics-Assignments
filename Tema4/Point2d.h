#pragma once
#include <iostream>

//-----------------------------------------------------------------------------------------------------
//	Point2d class holding information of a simple (x, y) point
//-----------------------------------------------------------------------------------------------------

class Point2d
{
public:
	Point2d();
	Point2d(int x, int y);
	~Point2d();

	Point2d& operator= (const Point2d &p2);
	Point2d& operator+= (const Point2d &p2);
	Point2d& operator-= (const Point2d &p2);
	const Point2d operator+ (const Point2d &p2) const;
	const Point2d operator- (const Point2d &p2) const;
	bool operator== (const Point2d &p2) const;
	bool operator!= (const Point2d &p2) const;

	friend std::ostream& operator<< (std::ostream& os, const Point2d &p);
	friend std::istream& operator>> (std::istream& is, Point2d &p);

public:
	int x, y;
};



