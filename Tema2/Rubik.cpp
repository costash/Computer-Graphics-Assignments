#include "HeadersAndDefines.h"
#include "Rubik.h"

//-----------------------------------------------------------------------------------------------------
//	Rubik class extending Object3d
//-----------------------------------------------------------------------------------------------------

Rubik::Rubik(unsigned int size, float cubeSize)
	: size(size), cubeSize(cubeSize), spaceBetweenCubes(1.f), rotXinProgress(false),
	rotYinProgress(false), rotZinProgress(false), rotationAngle(0.f)
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

unsigned int Rubik::linear3index(unsigned int i, unsigned int j, unsigned int k)
{
	return size * size * i + size * j + k;
}

// Rotation for layers
void Rubik::rotateLayerX(unsigned int layer, float angle)
{
	if (rotYinProgress || rotZinProgress)
		return;
	if (!rotXinProgress)
		rotationAngle = 0;
	rotationAngle += angle;
	Point3d center(.0f, .0f, .0f);
	for (unsigned int j = 0; j < size; ++j)
		for (unsigned int k = 0; k < size; ++k)
		{
			unsigned int idx = linear3index(layer, j, k);
			cubes[idx]->rotateXRelativeToPoint(center, angle);
		}

	if (abs(radiansToDegrees(rotationAngle)) % 90 == 0)
	{
		updateCubesPosition('X', layer, rotationAngle);
		rotXinProgress = false;
	}
	else
		rotXinProgress = true;
	std::cerr << "Angle " << rotationAngle << " grd " << abs(radiansToDegrees(rotationAngle)) << " rotationInProgress " << rotXinProgress << "\n";
}

void Rubik::rotateLayerY(unsigned int layer, float angle)
{
	if (rotXinProgress || rotZinProgress)
		return;
	if (!rotYinProgress)
		rotationAngle = 0;
	rotationAngle += angle;
	Point3d center(.0f, .0f, .0f);
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int k = 0; k < size; ++k)
		{
			unsigned int idx = linear3index(i, layer, k);
			cubes[idx]->rotateYRelativeToPoint(center, angle);
		}

	if (abs(radiansToDegrees(rotationAngle)) % 90 == 0)
		rotYinProgress = false;
	else
		rotYinProgress = true;
	std::cerr << "Angle " << rotationAngle << " grd " << abs(radiansToDegrees(rotationAngle)) << " rotationInProgress " << rotYinProgress << "\n";

}

void Rubik::rotateLayerZ(unsigned int layer, float angle)
{
	if (rotXinProgress || rotYinProgress)
		return;
	if (!rotZinProgress)
		rotationAngle = 0;
	rotationAngle += angle;
	Point3d center(.0f, .0f, .0f);
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int j = 0; j < size; ++j)
		{
			unsigned int idx = linear3index(i, j, layer);
			cubes[idx]->rotateZRelativeToPoint(center, angle);
		}

	if (abs(radiansToDegrees(rotationAngle)) % 90 == 0)
		rotZinProgress = false;
	else
		rotZinProgress = true;
	std::cerr << "Angle " << rotationAngle << " grd " << abs(radiansToDegrees(rotationAngle)) << " rotationInProgress " << rotZinProgress << "\n";
}

void Rubik::updateCubesPosition(char axis, unsigned int layer, float angle)
{
	switch(axis)
	{
	case 'X':
		{
			std::vector<Cube *> aux(cubes);
			if (radiansToDegrees(angle) >= 85)
			{
			
				for (unsigned int j = 0; j < size; ++j)
					for (unsigned int k = 0; k < size; ++k)
					{
						unsigned int c_idx = linear3index(layer, j, k);
						unsigned int aux_idx = linear3index(layer, size - k - 1, j);
						cubes[c_idx] = aux[aux_idx];
					}
			}
			else if (radiansToDegrees(angle) <= -85)
			{
				for (unsigned int j = 0; j < size; ++j)
					for (unsigned int k = 0; k < size; ++k)
					{
						unsigned int c_idx = linear3index(layer, size - k - 1, j);
						unsigned int aux_idx = linear3index(layer, j, k);
						cubes[c_idx] = aux[aux_idx];
					}
			}
		break;
		}
	case 'Y':
		break;
	case 'Z':
		break;
	default:
		break;
	}
}

// Helper function
static int radiansToDegrees(float rad)
{
	return int(rad * 180 / M_PI);
}