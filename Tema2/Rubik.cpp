#include "HeadersAndDefines.h"
#include "WorldDrawer3d.h"
#include "Rubik.h"

//-----------------------------------------------------------------------------------------------------
//	Rubik class extending Object3d
//-----------------------------------------------------------------------------------------------------

Rubik::Rubik(unsigned int size, float cubeSize)
	: size(size), cubeSize(cubeSize), spaceBetweenCubes(1.f), rotXinProgress(false),
	rotYinProgress(false), rotZinProgress(false), rotationAngle(0.f), rotationEndTime(0),
	selectedX(0), selectedY(0), selectedZ(0), updatedHighlightX(false), updatedHighlightY(false),
	updatedHighlightZ(false), selectEndTime(0)
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
				Cube *cube = new Cube(cubeSize, rubik_colors);
				cube->translate(cubeStep * i, cubeStep * j, cubeStep * k);
				cube->translate(-rubik_center, -rubik_center, -rubik_center);
				cubes.push_back(cube);
			}
	highlightSelectedLayers();
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
		angle = float(M_PI_2 - rotationAngle + angle);
		rotationAngle = float(M_PI_2);
	}
	else if (radiansToDegrees(rotationAngle) <= -85)
	{
		angle = float(-M_PI_2 - rotationAngle + angle);
		rotationAngle = float(-M_PI_2);
	}

	// Make the rotation
	Point3d center(.0f, .0f, .0f);
	for (unsigned int j = 0; j < size; ++j)
		for (unsigned int k = 0; k < size; ++k)
		{
			unsigned int idx = linear3index(layer, j, k);
			//if (!rotXinProgress)
			//	cubes[idx]->lightenColors(LIGHT_PERCENT);		// lighten colors for current face
			cubes[idx]->rotateXRelativeToPoint(center, angle);
		}

	// Update cubelets' position index in the array
	if (abs(radiansToDegrees(rotationAngle)) % 90 == 0)
	{
		rotationEndTime = WorldDrawer3d::getTime();		// current rotation end time
		
		unHighlightSelectedLayers();					// update highlight
		updateCubesPosition('X', layer, rotationAngle);
		highlightSelectedLayers();						// update highlight
		
		rotXinProgress = false;
		rotationAngle = 0;
		//// Reset colors back
		//for (unsigned int j = 0; j < size; ++j)
		//	for (unsigned int k = 0; k < size; ++k)
		//	{
		//		unsigned int idx = linear3index(layer, j, k);
		//		cubes[idx]->lightenColors(1 / LIGHT_PERCENT);
		//	}
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
		angle = float(M_PI_2 - rotationAngle + angle);
		rotationAngle = float(M_PI_2);
	}
	else if (radiansToDegrees(rotationAngle) <= -85)
	{
		angle = float(-M_PI_2 - rotationAngle + angle);
		rotationAngle = float(-M_PI_2);
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

		unHighlightSelectedLayers();					// update highlight
		updateCubesPosition('Y', layer, rotationAngle);
		highlightSelectedLayers();						// update highlight

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
		angle = float(M_PI_2 - rotationAngle + angle);
		rotationAngle = float(M_PI_2);
	}
	else if (radiansToDegrees(rotationAngle) <= -85)
	{
		angle = float(-M_PI_2 - rotationAngle + angle);
		rotationAngle = float(-M_PI_2);
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

		unHighlightSelectedLayers();					// update highlight
		updateCubesPosition('Z', layer, rotationAngle);
		highlightSelectedLayers();						// update highlight

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

void Rubik::highlightLayerX()
{
	for (unsigned int j = 0; j < size; ++j)
		for (unsigned int k = 0; k < size; ++k)
		{
			unsigned int idx = linear3index(selectedX, j, k);
			cubes[idx]->lightenColors(LIGHT_PERCENT);
		}
}

void Rubik::highlightLayerY()
{
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int k = 0; k < size; ++k)
		{
			unsigned int idx = linear3index(i, selectedY, k);
			cubes[idx]->lightenColors(LIGHT_PERCENT);
		}
}

void Rubik::highlightLayerZ()
{
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int j = 0; j < size; ++j)
		{
			unsigned int idx = linear3index(i, j, selectedZ);
			cubes[idx]->lightenColors(LIGHT_PERCENT);
		}
}

void Rubik::unHighlightLayerX()
{
	for (unsigned int j = 0; j < size; ++j)
		for (unsigned int k = 0; k < size; ++k)
		{
			unsigned int idx = linear3index(selectedX, j, k);
			cubes[idx]->lightenColors(1 / LIGHT_PERCENT);
		}
}

void Rubik::unHighlightLayerY()
{
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int k = 0; k < size; ++k)
		{
			unsigned int idx = linear3index(i, selectedY, k);
			cubes[idx]->lightenColors(1 / LIGHT_PERCENT);
		}
}

void Rubik::unHighlightLayerZ()
{
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int j = 0; j < size; ++j)
		{
			unsigned int idx = linear3index(i, j, selectedZ);
			cubes[idx]->lightenColors(1 / LIGHT_PERCENT);
		}
}

void Rubik::highlightSelectedLayers()
{
	highlightLayerX();
	highlightLayerY();
	highlightLayerZ();
}

void Rubik::unHighlightSelectedLayers()
{
	unHighlightLayerX();
	unHighlightLayerY();
	unHighlightLayerZ();
}

void Rubik::increaseSelectedX()
{
	if (WorldDrawer3d::getTime() - selectEndTime <= SELECT_SLEEP)
		return;
	unHighlightLayerX();
	selectedX = (selectedX + 1 + size) % size;
	highlightLayerX();

	selectEndTime = WorldDrawer3d::getTime();
}

void Rubik::increaseSelectedY()
{
	if (WorldDrawer3d::getTime() - selectEndTime <= SELECT_SLEEP)
		return;
	unHighlightLayerY();
	selectedY = (selectedY + 1 + size) % size;
	highlightLayerY();

	selectEndTime = WorldDrawer3d::getTime();
}

void Rubik::increaseSelectedZ()
{
	if (WorldDrawer3d::getTime() - selectEndTime <= SELECT_SLEEP)
		return;
	unHighlightLayerZ();
	selectedZ = (selectedZ + 1 + size) % size;
	highlightLayerZ();

	selectEndTime = WorldDrawer3d::getTime();
}

void Rubik::decreaseSelectedX()
{
	if (WorldDrawer3d::getTime() - selectEndTime <= SELECT_SLEEP)
		return;
	unHighlightLayerX();
	selectedX = (selectedX - 1 + size) % size;
	highlightLayerX();

	selectEndTime = WorldDrawer3d::getTime();
}

void Rubik::decreaseSelectedY()
{
	if (WorldDrawer3d::getTime() - selectEndTime <= SELECT_SLEEP)
		return;
	unHighlightLayerY();
	selectedY = (selectedY - 1 + size) % size;
	highlightLayerY();

	selectEndTime = WorldDrawer3d::getTime();
}

void Rubik::decreaseSelectedZ()
{
	if (WorldDrawer3d::getTime() - selectEndTime <= SELECT_SLEEP)
		return;
	unHighlightLayerZ();
	selectedZ = (selectedZ - 1 + size) % size;
	highlightLayerZ();

	selectEndTime = WorldDrawer3d::getTime();
}

bool Rubik::rotInProgress()
{
	return rotXinProgress || rotYinProgress || rotZinProgress;
}