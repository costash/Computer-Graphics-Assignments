#include "Circle2d.h"

const int NUM_TRIANGLES = 32;		// Number of triangles used to draw a circle
static const float TWICE_PI = (float)(2.0f * M_PI);	// Math constant 2 * pi
const float DELTA = .001f;			// Error precision of calculus

//-----------------------------------------------------------------------------------------------------
//	Circle2d class extending Object2d
//-----------------------------------------------------------------------------------------------------

// Creates a circle with radius 1 centered in the axis origin
Circle2d::Circle2d()
	: Object2d(std::vector<Point2d>(), std::vector<int>()),
	radius(1)
{
	init();
}

// Creates a circle with radius <param>radius</param> centered in the axis origin
Circle2d::Circle2d(float radius)
	: Object2d(std::vector<Point2d>(), std::vector<int>()),
	radius(radius)
{
	init();
}

Circle2d::~Circle2d()
{
}

// Scale overriding
void Circle2d::scale(float scaleFactor)
{
	for (unsigned int i = 1; i < this->points.size(); ++i)
		this->points[i].scale(scaleFactor, scaleFactor);

	radius *= scaleFactor;

	this->computeAxis();
}

// Relative scale overriding
void Circle2d::scaleRelativeToPoint(Point2d point, float scaleFactor)
{
	for (unsigned int i = 1; i < this->points.size(); ++i)
		this->points[i].scaleRelativeToPoint(point, scaleFactor, scaleFactor);

	radius *= scaleFactor;

	this->computeAxis();
}

// Helper method for circle creation
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
	computeAxis();
}

void Circle2d::rotateRelativeToPoint(Point2d pct, float angleRad)
{
	Object2d::rotateRelativeToPoint(pct, angleRad);
}

Point2d& Circle2d::getCenter()
{
	return points[0];
}