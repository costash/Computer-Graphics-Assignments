#pragma once
#include "support3d.h"
#include "Color.h"

//-----------------------------------------------------------------------------------------------------
//	Cube class extending Object3d
//-----------------------------------------------------------------------------------------------------


class Cube :
	public Object3d
{
public:
	Cube();
	Cube(float size);
	Cube(float size, Color colors[6]);
	~Cube();

	// Inherited from Object3d
	void scale(float scale);
	void scaleRelativeToPoint(Point3d p, float scale);

public:
	float size;
	Color colors[6];	// Color for each cube's side
	void draw();		// Inherited from Object3d

private:
	void init();	// Helper for constructor
};

