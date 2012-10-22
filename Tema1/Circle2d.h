#pragma once
#include "support2d.h"

//-----------------------------------------------------------------------------------------------------
//	Circle2d class extending Object2d
//-----------------------------------------------------------------------------------------------------
class Circle2d :
	public Object2d
{
public:
	Circle2d();
	Circle2d(float radius);
	virtual ~Circle2d();

	void scale(float scaleFactor);							// Overridden scale method from Object2d
	void scaleRelativeToPoint(Point2d p, float scaleFactor);// Overridden relative scale method from Object2d
public:
	float radius;											// Radius of the circle
private:
	void init();											// Helper for constructors
};

