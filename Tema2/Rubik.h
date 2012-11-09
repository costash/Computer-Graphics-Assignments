#pragma once
#include "support3d.h"
#include "Cube.h"

//-----------------------------------------------------------------------------------------------------
//	Rubik class
//-----------------------------------------------------------------------------------------------------

class Rubik
{
public:
	Rubik(unsigned int size, float cubeSize);
	~Rubik();

	void bindCoordSys(CoordinateSystem3d *cs);		// Must be called for the Rubik to be drawn

	// Rotation for layers
	void rotateLayerX(unsigned int layer, float angle);
	void rotateLayerY(unsigned int layer, float angle);
	void rotateLayerZ(unsigned int layer, float angle);

public:
	unsigned int size;			// Number of cubes per line
	float cubeSize;				// Dimension of a small cube
	std::vector<Cube *> cubes;	// Cublets that form the Rubik

	const float spaceBetweenCubes;
	
private:
	void init();
};

