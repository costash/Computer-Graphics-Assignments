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

	void bindCoordSys(CoordinateSystem3d *cs);
public:
	unsigned int size;			// Number of cubes per line
	float cubeSize;				// Dimension of a small cube
	std::vector<Cube *> cubes;	// Cublets that form the Rubik
	
private:
	void init();
};

