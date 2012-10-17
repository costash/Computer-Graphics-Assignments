#include "Rectangle2d.h"

//-----------------------------------------------------------------------------------------------------
//	Circle2d class extending Object2d
//-----------------------------------------------------------------------------------------------------

// Constructor and destructor
// Creates a rectangle with the center in origin with given length and height
Rectangle2d::Rectangle2d(float length, float height)
	: Object2d(std::vector<Point2d>(), std::vector<int>()),
	length(length),
	height(height)
{
	init();
}

Rectangle2d::~Rectangle2d()
{
}

// Helper for constructor
void Rectangle2d::init()
{
	// Corners from upper right to lower right counterclockwise
	points.push_back(Point2d(length / 2, height / 2));
	points.push_back(Point2d(-length / 2, height / 2));
	points.push_back(Point2d(-length / 2, -height / 2));
	points.push_back(Point2d(length / 2, -height / 2));

	topology.push_back(0);
	topology.push_back(1);
	topology.push_back(2);
	topology.push_back(2);
	topology.push_back(3);
	topology.push_back(0);

	computeAxis();
}