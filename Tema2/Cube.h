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
	void draw();										// Cube is drawn differently

	void setColors(Color colors[6]);					// Sets colors for cube sides
	void lightenColors(float lightPercent);				// Changes light of colors for faces

public:
	float size;			// Size of a cube's side
	Color colors[6];	// Color for each cube's side
	

private:
	void init();	// Helper for constructor
	void lightenColor(Color &col, float lightPercent);	// Changes light of color for a given color
};

