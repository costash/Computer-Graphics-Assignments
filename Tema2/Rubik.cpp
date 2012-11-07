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
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int j = 0; j < size; ++j)
			for (unsigned int k = 0; k < size; ++k)
			{
				Cube *cube = new Cube(cubeSize, colors);
				cube->translate((cubeSize + .2f) * i, (cubeSize + .2f) * j, (cubeSize + .2f) * k);
				cubes.push_back(cube);
			}
}

void Rubik::bindCoordSys(CoordinateSystem3d *cs)
{
	cs->objects.insert(cs->objects.end(), cubes.begin(), cubes.end());
}