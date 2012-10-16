#include "Circle2d.h"

#define  _USE_MATH_DEFINES
#include <math.h>

const int NUM_TRIANGLES = 20;
const float TWICE_PI = 2.0f * M_PI;
const float DELTA = .001f;

Circle2d::Circle2d()
	: Object2d(std::vector<Point2d>(), std::vector<int>()),
	radius(1)
{
	init();
}

Circle2d::Circle2d(float radius)
	: Object2d(std::vector<Point2d>(), std::vector<int>()),
	radius(radius)
{
	init();
}


Circle2d::~Circle2d()
{
}

void Circle2d::init()
{
	this->points.push_back(Point2d(0, 0));

	for (float i = 0; abs(i - TWICE_PI) > DELTA; i += TWICE_PI / NUM_TRIANGLES)
		this->points.push_back(Point2d( radius * cos(i), radius * sin(i)));

	for (int i = 1; i <= NUM_TRIANGLES; ++i)
	{
		this->topology.push_back(0);
		this->topology.push_back(i);
		if (i != NUM_TRIANGLES)
			this->topology.push_back(i + 1);
		else
			this->topology.push_back(1);
	}
}