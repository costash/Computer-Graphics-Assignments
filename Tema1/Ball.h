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
	virtual void rotateRelativeToPoint(Point2d pct, float angleRad);//rotatie relativa la punctul p

private:
	void init();
public:
	Point2d previews_center;
	Point2d current_center;
	bool posessed;
	Object2d* at_player;
};

