#include "Rubik.h"
#include "HeadersAndDefines.h"

//-----------------------------------------------------------------------------------------------------
//	Rubik class extending Object3d
//-----------------------------------------------------------------------------------------------------

Rubik::Rubik(unsigned int size, float cubeSize)
	: size(size), cubeSize(cubeSize), spaceBetweenCubes(.2f)
{
	init();


}


Rubik::~Rubik()
{
}

void Rubik::init()
{
	float cubeStep = cubeSize + spaceBetweenCubes;		// Cube size + space between cubes
	float rubik_center = (size - 1) * cubeStep / 2;		// Center of Rubik cube
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int j = 0; j < size; ++j)
			for (unsigned int k = 0; k < size; ++k)
			{
				Cube *cube = new Cube(cubeSize, colors);
				cube->translate(cubeStep * i, cubeStep * j, cubeStep * k);
				cube->translate(-rubik_center, -rubik_center, -rubik_center);
				cubes.push_back(cube);
			}
}

void Rubik::bindCoordSys(CoordinateSystem3d *cs)
{
	cs->objects.insert(cs->objects.end(), cubes.begin(), cubes.end());
}

//// Rotation for layers
//	void rotateLayerX(unsigned int layer, float angle);
//	void rotateLayerY(unsigned int layer, float angle);
//	void rotateLayerZ(unsigned int layer, float angle);
void Rubik::rotateLayerX(unsigned int layer, float angle)
{
	Point3d center(.0f, .0f, .0f);
	for (unsigned int j = 0; j < size; ++j)
		for (unsigned int k = 0; k < size; ++k)
		{
			unsigned int idx = layer * size * size + j * size + k;
			cubes[idx]->rotateXRelativeToPoint(center, angle);
		}

}

void Rubik::rotateLayerY(unsigned int layer, float angle)
{
}

void Rubik::rotateLayerZ(unsigned int layer, float angle)
{
}