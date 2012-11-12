//-----------------------------------------------------------------------------------------------
//					Tema 2 - Rubik's Cube
//
//	Fisiere de interes: Transform3d.cpp main.cpp
//
//	Functii WorldDrawer3d:
//	-init e apelat o singura data, la inceput.
//	-idle e apelat per frame
//	-onKey la apasarea unei taste.
//
//	Obiecte:
//	- un obiect este reprezentat prin punct si topologia punctelor (cum sunt legate pctele)
//	- obiectele sunt compuse din triunghiuri! de exemplu cu 4 puncte si 6 indici de topologie
//	pot crea 2 triunghiuri adiacente ce impreuna formeaza un dreptunghi.
//
//	Sisteme de coordonate:
//	- sunt 2 tipuri de sisteme de coordonate (fix - bleu&magenta) si dinamic(rosu&albastru)
//	- ca un obiect sa fie desenat trebuie sa fie atasat unui sistem de coordonate
//	- cand un obiect e atasat la un sistem de coordonate urmeaza transformarile sistemului.
//
//	Control obiecte:
//	- daca translatez/rotesc un obiect/punct direct (ex: o->translate(1,1)) o fac in coordonate globale
//	- daca translatez/rotesc un obiect printr-un sistem de coordonate o fac in coordonate locale
//	- pentru simplitate toate coordonatele mentinute in obiecte(de c++) sunt globale.
//
//	Happy coding.
//----------------------------------------------------------------------------------------------

#include "WorldDrawer3d.h"
#include "Cube.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Rubik.h"

bool WorldDrawer3d::animation=true;
bool WorldDrawer3d::keyStates[256];
bool WorldDrawer3d::keySpecialStates[256];
unsigned int WorldDrawer3d::tick = 0;

bool WorldDrawer3d::windowCreated = false;
int WorldDrawer3d::secondaryWindow;


//used global vars
CoordinateSystem3d *cs1;

Rubik *rubik;

//add
void WorldDrawer3d::init(){
	//creeaza 2 sistem de coordonate client
	cs1 = new CoordinateSystem3d();
	cs_used.push_back(cs1);

	tick = glutGet(GLUT_ELAPSED_TIME);
	
	rubik = new Rubik(5, 3.f);		// Create a Rubik cube with 5 cubes of size 3
	rubik->bindCoordSys(cs1);		// Bind it's cubelets to the coord system
}

// Is called in glut main loop by the system on idle
void WorldDrawer3d::onIdle(){	//per frame
	keyOperations();			// Operations for buffered keys

	if(animation){
		// Do nothing here
	}
}

// Draws text on screen
void WorldDrawer3d::drawText(float posx, float posy, float posz, Color col, const unsigned char * text)
{
	glPushMatrix();						// Save context
	glColor3f(col.r, col.g, col.b);		// Text color
	glRasterPos3f(posx, posy, posz);	// Place text
	char *c = (char *)text;				// Draw each character
	for (; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	
	glPopMatrix();						// Restore context
}

// Draws the current score
void WorldDrawer3d::drawScore(float posx, float posy, float posz, Color col)
{
	std::stringstream ss;
	if (rubik->state == 0)		// Game not started
		ss << "Game did not start yet. Press ENTER to start counting.";
	else if(rubik->state == 1 || rubik->state == 2)		// Game started or is won
		ss << "Game started. Rotated " << rubik->moves << " times until now.";

	const std::string& tmp = ss.str();
	const char* cstr = tmp.c_str();
	//std::cerr << cstr;
	drawText(posx, posy, posz, col, (const unsigned char *)cstr);
}

// Draws the text for win
void WorldDrawer3d::drawWin(float posx, float posy, float posz, Color col)
{
	if (rubik->state == 2)		// Game is won
		drawText(posx, posy, posz, col, (const unsigned char *)"You win! Press 1 to reset or ENTER to start counting.");
}

// All key events are processed here
void WorldDrawer3d::keyOperations()
{
	if (keyStates[KEY_ESC])			// On Escape, program exits
		glutExit();
	
	// Arrow keys rotate the entire cube
	float rotateStep = 2.f;

	if (keySpecialStates[KEY_UP])			// Rotate cube up
	{
		//std::cerr << "UP was pressed\n";
		viewAngleY -= rotateStep;
	}
	if (keySpecialStates[KEY_DOWN])			// Rotate cube down
	{
		//std::cerr << "DOWN was pressed\n";
		viewAngleY += rotateStep;
	}
	if (keySpecialStates[KEY_LEFT])			// Rotate cube left
	{
		//std::cerr << "LEFT was pressed\n";
		viewAngleX -= rotateStep;
	}
	if (keySpecialStates[KEY_RIGHT])		// Rotate cube right
	{
		//std::cerr << "RIGHT was pressed\n";
		viewAngleX += rotateStep;
	}

	// Move the cube forwards and backwards
	float eyeDistanceStep = 1.f;

	if (keyStates['['])
	{
		//std::cerr << "[ was pressed\n";
		eyeDistance -= eyeDistanceStep;		// Move closer to the viewer
	}
	if (keyStates[']'])
	{
		//std::cerr << "] was pressed\n";
		eyeDistance += eyeDistanceStep;		// Move farther from the viewer
	}

	// Rotate faces
	float faceRotateStep = float(M_PI_4 / 24);
	if (keyStates['q'])								// Rotate on X axis, positive
	{
		//std::cerr << "q was pressed\n";
		rubik->rotateLayerX(rubik->selectedX, faceRotateStep);
	}
	if (keyStates['a'])								// Rotate on X axis, negative
	{
		//std::cerr << "a was pressed\n";
		rubik->rotateLayerX(rubik->selectedX, -faceRotateStep);
	}
	if (keyStates['w'])								// Rotate on Y axis, positive
	{
		//std::cerr << "w was pressed\n";
		rubik->rotateLayerY(rubik->selectedY, faceRotateStep);
	}
	if (keyStates['s'])								// Rotate on Y axis, negative
	{
		//std::cerr << "s was pressed\n";
		rubik->rotateLayerY(rubik->selectedY, -faceRotateStep);
	}
	if (keyStates['e'])								// Rotate on Z axis, positive
	{
		//std::cerr << "e was pressed\n";
		rubik->rotateLayerZ(rubik->selectedZ, faceRotateStep);
	}
	if (keyStates['d'])								// Rotate on Z axis, negative
	{
		//std::cerr << "d was pressed\n";
		rubik->rotateLayerZ(rubik->selectedZ, -faceRotateStep);
	}

	// Select layers (increase/decrease)
	if (keyStates['t'])								// Increase selection on X axis
	{
		//std::cerr << "t was pressed\n";
		if (!rubik->rotInProgress())
			rubik->increaseSelectedX();
	}
	if (keyStates['g'])								// Decrease selection on X axis
	{
		//std::cerr << "g was pressed\n";
		if (!rubik->rotInProgress())
			rubik->decreaseSelectedX();
	}
	if (keyStates['y'])								// Increase selection on Y axis
	{
		//std::cerr << "y was pressed\n";
		if (!rubik->rotInProgress())
			rubik->increaseSelectedY();
	}
	if (keyStates['h'])								// Decrease selection on Y axis
	{
		//std::cerr << "h was pressed\n";
		if (!rubik->rotInProgress())
			rubik->decreaseSelectedY();
	}
	if (keyStates['u'])								// Increase selection on Z axis
	{
		//std::cerr << "u was pressed\n";
		if (!rubik->rotInProgress())
			rubik->increaseSelectedZ();
	}
	if (keyStates['j'])								// Decrease selection on Z axis
	{
		//std::cerr << "j was pressed\n";
		if (!rubik->rotInProgress())
			rubik->decreaseSelectedZ();
	}

	// Start counting moves
	if (keyStates['\r'])							// If ENTER is pressed, game starts
	{
		//std::cerr << "enter was pressed\n";
		//std::cerr << "game state: " << rubik->state << "\n";
		if (rubik->state != 1)
		{
			if (rubik->state == 2)
				rubik->moves = 0;
			rubik->state = 1;
			
		}
	}

	// Reset game
	if (keyStates['1'])								// If 1 is pressedm, game is reset
	{
		cs1->objects.clear();
		rubik->reset();
		rubik->bindCoordSys(cs1);
	}
}

// Callback function for mouse actions
void WorldDrawer3d::mouseCallbackFunction(int button, int state, int x, int y)
{
	mousePosX = float (x);
	mousePosY = float (y);
	if (button == MOUSE_LEFT)			// Buffer left clicks
	{
		if (state == GLUT_DOWN)
			mouseLeftState = true;
		else if (state == GLUT_UP)
			mouseLeftState = false;
	}
	else if (button == MOUSE_RIGHT)		// Buffer right clicks
	{
		if (state == GLUT_DOWN)
			mouseRightState = true;
		else if (state == GLUT_UP)
			mouseRightState = false;
	}
}

// Callback for mouse movement
void WorldDrawer3d::mouseMotionCallbackFunction(int x, int y)
{
	float eyeDistanceStep = 0.2f;
	if (mouseLeftState == true)			// Make rotation if left is clicked and moved mouse
	{
		//std::cerr << "(" << mousePosX << "," << mousePosY << ") MouseLeft ";
		viewAngleX += (x - mousePosX);
		viewAngleY += (y - mousePosY);
		mousePosX = float(x);
		mousePosY = float(y);
	}
	if (mouseRightState == true)		// Make zoom in/out if right is clicked and moved
	{
		//std::cerr << "(" << mousePosX << "," << mousePosY << ") MouseRight ";
		eyeDistance -= (y - mousePosY) * eyeDistanceStep;
		mousePosY = float (y);
	}
}

// Callback for mouse scroll (wheel)
void WorldDrawer3d::mouseWheelCallbackFunction(int wheel, int direction, int x, int y)
{
	float eyeDistanceStep = 2.f;
	eyeDistance += eyeDistanceStep * (-direction);
}


int main(int argc, char** argv){
	WorldDrawer3d wd3d(argc,argv,600,600,200,100,std::string("Tema 2: Rubik Cube"));
	wd3d.init();
	wd3d.run();
	return 0;
}