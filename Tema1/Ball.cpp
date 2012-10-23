#include "Ball.h"

//-----------------------------------------------------------------------------------------------------
//	Ball class extending Circle2d
//-----------------------------------------------------------------------------------------------------
Ball::Ball()
	: Circle2d()
{
	this->init();
}

Ball::Ball(float radius)
	: Circle2d(radius)
{
	this->init();
}


Ball::~Ball()
{
}

void Ball::init()
{
	current_center = Point2d(0, 0);
	previews_center = Point2d(0, 0);
	at_player = &Circle2d(0);
	posessed = false;
}

void Ball::translate(float x, float y)
{
	Object2d::translate(x, y);
	// Also move the previews center
	previews_center.x = current_center.x;
	previews_center.y = current_center.y;
	current_center.translate(x, y);
}

void Ball::rotateRelativeToPoint(Point2d pct, float angleRad)
{
	previews_center = current_center;
	Circle2d::rotateRelativeToPoint(pct, angleRad);
	current_center.rotateRelativeToPoint(pct, angleRad);
}