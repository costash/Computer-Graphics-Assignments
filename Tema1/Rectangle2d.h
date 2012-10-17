#pragma once
#include "support2d.h"

//-----------------------------------------------------------------------------------------------------
//	Circle2d class extending Object2d
//-----------------------------------------------------------------------------------------------------
class Rectangle2d :
	public Object2d
{
public:
	Rectangle2d(Point2d downLeft, Point2d upRight);
	~Rectangle2d();
public:
	Point2d downLeft;		// Corner from bottom left side of the rectangle
	Point2d upRight;		// Corner from the top right side of the rectangle
private:
	void init();			// Helper method for constructor
};

