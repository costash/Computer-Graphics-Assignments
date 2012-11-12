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
	void reset();

	// Rotation for layers
	void rotateLayerX(unsigned int layer, float angle);
	void rotateLayerY(unsigned int layer, float angle);
	void rotateLayerZ(unsigned int layer, float angle);

	// Gets the linearized index for i,j,k tuple that would represent the 3 dimensions
	unsigned int linear3index(unsigned int i, unsigned int j, unsigned int k);

	// Helpers
	static int radiansToDegrees(float rad);

	// Select layers
	void highlightLayerX();
	void highlightLayerY();
	void highlightLayerZ();
	void unHighlightLayerX();
	void unHighlightLayerY();
	void unHighlightLayerZ();
	void highlightSelectedLayers();
	void unHighlightSelectedLayers();

	void increaseSelectedX();
	void increaseSelectedY();
	void increaseSelectedZ();
	void decreaseSelectedX();
	void decreaseSelectedY();
	void decreaseSelectedZ();

	bool rotInProgress();

	bool isVictory();

public:
	unsigned int size;			// Number of cubes per line
	float cubeSize;				// Dimension of a small cube
	std::vector<Cube *> cubes;	// Cublets that form the Rubik

	std::vector<Cube *> initialCubesPositions;

	const float spaceBetweenCubes;							// Space to be added between cubelets
	bool rotXinProgress, rotYinProgress, rotZinProgress;	// Wether a rotation is in progress or not
	float rotationAngle;									// Rotation angle for current layer rotation
	unsigned int rotationEndTime;							// The moment when the rotation ended
	unsigned int selectedX, selectedY, selectedZ;			// Specifies the selected layer
	bool updatedHighlightX, updatedHighlightY, updatedHighlightZ;

	unsigned int selectEndTime;								// The moment when the selection ended
	unsigned int state;			// state of the Game
	unsigned int moves;			// Moves since game started

private:
	void init();				// Inits the Rubik for the first time
	// Updates the cubelets positions in the Rubik based on previews layer rotations
	void updateCubesPosition(char axis, unsigned int layer, float angle);
};

const unsigned int ROT_SLEEP = 200;
const float LIGHT_PERCENT = 0.8f;
const unsigned int SELECT_SLEEP = 200;