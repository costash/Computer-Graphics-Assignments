#pragma once

//-----------------------------------------------------------------------------------------------------
//	Ball class extending Circle2d
//-----------------------------------------------------------------------------------------------------
#include "Circle2d.h"
class Ball :
	public Circle2d
{
public:
	Ball();
	Ball(float radius);
	~Ball();

	void translate(float x, float y);						//translatie

private:
	void init();
public:
	Point2d previews_center;
	Point2d current_center;
};

