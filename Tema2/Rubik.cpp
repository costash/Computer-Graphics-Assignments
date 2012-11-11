#include "HeadersAndDefines.h"
#include "WorldDrawer3d.h"
#include "Rubik.h"

//-----------------------------------------------------------------------------------------------------
//	Rubik class extending Object3d
//-----------------------------------------------------------------------------------------------------

Rubik::Rubik(unsigned int size, float cubeSize)
	: size(size), cubeSize(cubeSize), spaceBetweenCubes(1.f), rotXinProgress(false),
	rotYinProgress(false), rotZinProgress(false), rotationAngle(0.f), rotationEndTime(0)
{
	init();
}

Rubik::~Rubik()
{
}

// Initializes the Rubik cube for the first time
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

// Adds cubelets to a coordinate system to be drawn
void Rubik::bindCoordSys(CoordinateSystem3d *cs)
{
	cs->objects.insert(cs->objects.end(), cubes.begin(), cubes.end());
}

// Helper to linearize 3 indexes i, j, k
unsigned int Rubik::linear3index(unsigned int i, unsigned int j, unsigned int k)
{
	return size * size * i + size * j + k;
}

// Rotation for layers
void Rubik::rotateLayerX(unsigned int layer, float angle)
{
	// Check if rotation can be made
	if (rotYinProgress || rotZinProgress || (WorldDrawer3d::getTime() - rotationEndTime) <= ROT_SLEEP)
		return;
	if (!rotXinProgress)
		rotationAngle = 0;
	rotationAngle += angle;

	// If rotation is almost 90 or -90 degrees snap the cube to be exactly 90/-90
	if (radiansToDegrees(rotationAngle) >= 85)
	{
		angle = (M_PI_2 - rotationAngle + angle);
		rotationAngle = M_PI_2;
	}
	else if (radiansToDegrees(rotationAngle) <= -85)
	{
		angle = (-M_PI_2 - rotationAngle + angle);
		rotationAngle = -M_PI_2;
	}

	// Make the rotation
	Point3d center(.0f, .0f, .0f);
	for (unsigned int j = 0; j < size; ++j)
		for (unsigned int k = 0; k < size; ++k)
		{
			unsigned int idx = linear3index(layer, j, k);
			cubes[idx]->rotateXRelativeToPoint(center, angle);
		}

	// Update cubelets' position index in the array
	if (abs(radiansToDegrees(rotationAngle)) % 90 == 0)
	{
		rotationEndTime = WorldDrawer3d::getTime();		// current rotation end time
		updateCubesPosition('X', layer, rotationAngle);
		rotXinProgress = false;
		rotationAngle = 0;
	}
	else
		rotXinProgress = true;
	std::cerr << "Angle " << rotationAngle << " grd " << radiansToDegrees(rotationAngle) << " rotationInProgress " << rotXinProgress << "\n";
}

void Rubik::rotateLayerY(unsigned int layer, float angle)
{
	// Check if rotation can be made
	if (rotXinProgress || rotZinProgress || (WorldDrawer3d::getTime() - rotationEndTime) <= ROT_SLEEP)
		return;
	if (!rotYinProgress)
		rotationAngle = 0;
	rotationAngle += angle;

	// If rotation is almost 90 or -90 degrees snap the cube to be exactly 90/-90
	if (radiansToDegrees(rotationAngle) >= 85)
	{
		angle = (M_PI_2 - rotationAngle + angle);
		rotationAngle = M_PI_2;
	}
	else if (radiansToDegrees(rotationAngle) <= -85)
	{
		angle = (-M_PI_2 - rotationAngle + angle);
		rotationAngle = -M_PI_2;
	}

	// Make the rotation
	Point3d center(.0f, .0f, .0f);
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int k = 0; k < size; ++k)
		{
			unsigned int idx = linear3index(i, layer, k);
			cubes[idx]->rotateYRelativeToPoint(center, angle);
		}

	// Update cubelets' position index in the array
	if (abs(radiansToDegrees(rotationAngle)) % 90 == 0)
	{
		rotationEndTime = WorldDrawer3d::getTime();		// current rotation end time
		updateCubesPosition('Y', layer, rotationAngle);
		rotYinProgress = false;
		rotationAngle = 0;
	}
	else
		rotYinProgress = true;
	std::cerr << "Angle " << rotationAngle << " grd " << radiansToDegrees(rotationAngle) << " rotationInProgress " << rotYinProgress << "\n";
}

void Rubik::rotateLayerZ(unsigned int layer, float angle)
{
	// Check if rotation can be made
	if (rotXinProgress || rotYinProgress || (WorldDrawer3d::getTime() - rotationEndTime) <= ROT_SLEEP)
		return;
	if (!rotZinProgress)
		rotationAngle = 0;
	rotationAngle += angle;

	// If rotation is almost 90 or -90 degrees snap the cube to be exactly 90/-90
	if (radiansToDegrees(rotationAngle) >= 85)
	{
		angle = (M_PI_2 - rotationAngle + angle);
		rotationAngle = M_PI_2;
	}
	else if (radiansToDegrees(rotationAngle) <= -85)
	{
		angle = (-M_PI_2 - rotationAngle + angle);
		rotationAngle = -M_PI_2;
	}

	// Make the rotation
	Point3d center(.0f, .0f, .0f);
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int j = 0; j < size; ++j)
		{
			unsigned int idx = linear3index(i, j, layer);
			cubes[idx]->rotateZRelativeToPoint(center, angle);
		}

	// Update cubelets' position index in the array
	if (abs(radiansToDegrees(rotationAngle)) % 90 == 0)
	{
		rotationEndTime = WorldDrawer3d::getTime();		// current rotation end time
		updateCubesPosition('Z', layer, rotationAngle);
		rotZinProgress = false;
		rotationAngle = 0;
	}
	else
		rotZinProgress = true;
	std::cerr << "Angle " << rotationAngle << " grd " << radiansToDegrees(rotationAngle) << " rotationInProgress " << rotZinProgress << "\n";
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
				// Counter-clockwise rotation
				for (unsigned int j = 0; j < size; ++j)
					for (unsigned int k = 0; k < size; ++k)
					{
						unsigned int c_idx = linear3index(layer, size - k - 1, j);
						unsigned int aux_idx = linear3index(layer, j, k);
						cubes[c_idx] = aux[aux_idx];
					}
			}
			else if (radiansToDegrees(angle) <= -85)
			{
				// Clockwise rotation
				for (unsigned int j = 0; j < size; ++j)
					for (unsigned int k = 0; k < size; ++k)
					{
						unsigned int c_idx = linear3index(layer, j, k);
						unsigned int aux_idx = linear3index(layer, size - k - 1, j);
						cubes[c_idx] = aux[aux_idx];
					}
			}
		break;
		}
	case 'Y':
		{
			std::vector<Cube *> aux(cubes);
			if (radiansToDegrees(angle) >= 85)
			{
				// Counter-clockwise rotation
				for (unsigned int i = 0; i < size; ++i)
					for (unsigned int k = 0; k < size; ++k)
					{
						unsigned int c_idx = linear3index(k, layer, i);
						unsigned int aux_idx = linear3index(size - i - 1, layer, k);
						cubes[c_idx] = aux[aux_idx];
					}
			}
			else if (radiansToDegrees(angle) <= -85)
			{
				// Clockwise rotation
				for (unsigned int i = 0; i < size; ++i)
					for (unsigned int k = 0; k < size; ++k)
					{
						unsigned int c_idx = linear3index(size - i - 1, layer, k);
						unsigned int aux_idx = linear3index(k, layer, i);
						cubes[c_idx] = aux[aux_idx];
					}
			}
		}
		break;
	case 'Z':
		{
			std::vector<Cube *> aux(cubes);
			if (radiansToDegrees(angle) >= 85)
			{
				// Counter-clockwise rotation
				for (unsigned int i = 0; i < size; ++i)
					for (unsigned int j = 0; j < size; ++j)
					{
						unsigned int c_idx = linear3index(j, i, layer);
						unsigned int aux_idx = linear3index(i, size - j - 1, layer);
						cubes[c_idx] = aux[aux_idx];
					}
			}
			else if (radiansToDegrees(angle) <= -85)
			{
				// Clockwise rotation
				for (unsigned int i = 0; i < size; ++i)
					for (unsigned int j = 0; j < size; ++j)
					{
						unsigned int c_idx = linear3index(i, size - j - 1, layer);
						unsigned int aux_idx = linear3index(j, i, layer);
						cubes[c_idx] = aux[aux_idx];
					}
			}
		}
		break;
	default:
		break;
	}
}

// Helper function
int Rubik::radiansToDegrees(float rad)
{
	return int(rad * 180 / M_PI);
}