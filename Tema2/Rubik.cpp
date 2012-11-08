#include "Rubik.h"
#include "HeadersAndDefines.h"

//-----------------------------------------------------------------------------------------------------
//	Rubik class extending Object3d
//-----------------------------------------------------------------------------------------------------

Rubik::Rubik(unsigned int size, float cubeSize)
	: size(size), cubeSize(cubeSize)
{
	init();


}


Rubik::~Rubik()
{
}

void Rubik::init()
{
	float cubeStep = cubeSize + .2f;	// Cube size + space between cubes
	float rubik_center = (size - 1) * cubeStep / 2;		// Center of Rubik cube
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int j = 0; j < size; ++j)
			for (unsigned int k = 0; k < size; ++k)
			{
				Cube *cube = new Cube(cubeSize, colors);
				cube->translate((cubeSize + .2f) * i, (cubeSize + .2f) * j, (cubeSize + .2f) * k);
				cube->translate(-rubik_center, -rubik_center, -rubik_center);
				cubes.push_back(cube);
			}
}

void Rubik::bindCoordSys(CoordinateSystem3d *cs)
{
	cs->objects.insert(cs->objects.end(), cubes.begin(), cubes.end());
}