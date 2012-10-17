#pragma once
#include "support2d.h"

//-----------------------------------------------------------------------------------------------------
//	Circle2d class extending Object2d
//-----------------------------------------------------------------------------------------------------
class Rectangle2d :
	public Object2d
{
public:
	Rectangle2d(float length, float height);
	~Rectangle2d();
public:
	float length;		// Length of the rectangle
	float height;		// Height of the rectangle
private:
	void init();			// Helper method for constructor
};

