#include "Cube.h"
#include "HeadersAndDefines.h"

//-----------------------------------------------------------------------------------------------------
//	Cube class extending Object3d
//-----------------------------------------------------------------------------------------------------

Cube::Cube()
	: Object3d(std::vector<Point3d>(), std::vector<int>()),
	size(2)
{
	init();

	computeAxis();
}

Cube::Cube(float size)
	: Object3d(std::vector<Point3d>(), std::vector<int>()),
	size(size)
{
	init();
	for (int i = 0; i < 6; ++i)
		colors[i] = Color();

	scaleRelativeToPoint(axiscenter, size / 2);

	computeAxis();
}

Cube::Cube(float size, Color colors[6])
	: Object3d(std::vector<Point3d>(), std::vector<int>()),
	size(size)
{
	init();
	for (int i = 0; i < 6; ++i)
	{
		this->colors[i] = colors[i];
	}

	scaleRelativeToPoint(axiscenter, size / 2);

	computeAxis();
}


Cube::~Cube()
{
}

void Cube::init()
{
	//               v4.-----------.v1
	//                /           /|
	//               /           / |
	//            v3.-----------.v2|
	//              |           |  |
	//              |  .v8      |  .v5
	//              |           | /
	//            v7|___________|/v6
	//
	points.push_back(Point3d(1,1,1));		// v1
	points.push_back(Point3d(1,1,-1));		// v2
	points.push_back(Point3d(-1,1,-1));		// v3
	points.push_back(Point3d(-1,1,1));		// v4
	points.push_back(Point3d(1,-1,1));		// v5
	points.push_back(Point3d(1,-1,-1));		// v6
	points.push_back(Point3d(-1,-1,-1));	// v7
	points.push_back(Point3d(-1,-1,1));		// v8
	topology.push_back(0);topology.push_back(1);topology.push_back(2);	//top
	topology.push_back(2);topology.push_back(3);topology.push_back(0);

	topology.push_back(6);topology.push_back(5);topology.push_back(4);	//bottom
	topology.push_back(7);topology.push_back(4);topology.push_back(6);

	topology.push_back(2);topology.push_back(3);topology.push_back(6);	//left
	topology.push_back(7);topology.push_back(3);topology.push_back(6);

	topology.push_back(0);topology.push_back(1);topology.push_back(5);	//right
	topology.push_back(0);topology.push_back(5);topology.push_back(4);

	topology.push_back(0);topology.push_back(3);topology.push_back(4);	//front
	topology.push_back(7);topology.push_back(3);topology.push_back(4);

	topology.push_back(5);topology.push_back(1);topology.push_back(2);	//back
	topology.push_back(6);topology.push_back(2);topology.push_back(5);
}

// Scale cube
void Cube::scale(float scale)
{
	Object3d::scale(scale, scale, scale);

	size *= scale;
}

// Scale cube relative to a point
void Cube::scaleRelativeToPoint(Point3d p, float scale)
{
	Object3d::scaleRelativeToPoint(p, scale, scale, scale);

	size *= scale;
}

// Draw method called in draw callback
void Cube::draw()
{
	// Draw the object
	glBegin(GL_TRIANGLES);
	for (unsigned int side = 0; side < 6; ++side)
	{
		glColor3f(colors[side].r, colors[side].g, colors[side].b);
		for (unsigned int idx = 0; idx < 6; ++idx)
		{
			int index = topology[side * 6 + idx];
			glVertex3f(points[index].x, points[index].y, points[index].z);
		}
	}
	glEnd();

	// Draw object's axis
	glLineWidth(2);
	if (draw_axis)
	{
		glBegin(GL_LINES);
			glColor3f(0, 1, 0);	// Axis up is Green
			glVertex3f(axiscenter.x, axiscenter.y, axiscenter.z);
			glVertex3f(axisup.x, axisup.y, axisup.z);

			glColor3f(1, 0, 0);	// Axis right is Red
			glVertex3f(axiscenter.x, axiscenter.y, axiscenter.z);
			glVertex3f(axisright.x, axisright.y, axisright.z);

			glColor3f(0, 0, 1);	// Axis forward is Blue
			glVertex3f(axiscenter.x, axiscenter.y, axiscenter.z);
			glVertex3f(axisfwd.x, axisfwd.y, axisfwd.z);
		glEnd();
	}
}