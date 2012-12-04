#include "Point2d.h"

//-----------------------------------------------------------------------------------------------------
//	Point2d class holding information of a simple (x, y) point
//-----------------------------------------------------------------------------------------------------

Point2d::Point2d()
	: x(0), y(0)
{
}

Point2d::Point2d(int x, int y)
	: x(x), y(y)
{
}

Point2d::~Point2d()
{
}

Point2d& Point2d::operator= (const Point2d &p2)
{
	if (this != &p2)
	{
		x = p2.x;
		y = p2.y;
	}
	return *this;
}

Point2d& Point2d::operator+= (const Point2d &p2)
{
	x += p2.x;
	y += p2.y;

	return *this;
}

Point2d& Point2d::operator-= (const Point2d &p2)
{
	x -= p2.x;
	y -= p2.y;

	return *this;
}

const Point2d Point2d::operator+ (const Point2d &p2) const
{
	return Point2d(*this) += p2;
}

const Point2d Point2d::operator- (const Point2d &p2) const
{
	return Point2d(*this) -= p2;
}

bool Point2d::operator== (const Point2d &p2) const
{
	return x == p2.x && y == p2.y;
}

bool Point2d::operator!= (const Point2d &p2) const
{
	return x != p2.x || y != p2.y;
}

std::ostream& operator<< (std::ostream& os, const Point2d &p)
{
	os << "(" << p.x << "," << p.y << ")";
	return os;
}

std::istream& operator>> (std::istream& is, Point2d &p)
{
	is >> p.x >> p.y;
	return is;
}