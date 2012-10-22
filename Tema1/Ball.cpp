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
}

void Ball::translate(float x, float y)
{
	Object2d::translate(x, y);
	// Also move the previews center
	previews_center.x = current_center.x;
	previews_center.y = current_center.y;
	current_center.translate(x, y);
}