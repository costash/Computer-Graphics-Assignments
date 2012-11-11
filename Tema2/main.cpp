//-----------------------------------------------------------------------------------------------
//					LAB 2
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
#include "Rubik.h"

bool WorldDrawer3d::animation=true;
bool WorldDrawer3d::keyStates[256];
bool WorldDrawer3d::keySpecialStates[256];
unsigned int WorldDrawer3d::tick = 0;


//used global vars
CoordinateSystem3d *cs1;

Rubik *rubik;

//add
void WorldDrawer3d::init(){
	//creeaza 2 sistem de coordonate client
	cs1 = new CoordinateSystem3d();
	cs_used.push_back(cs1);

	tick = glutGet(GLUT_ELAPSED_TIME);
	
	rubik = new Rubik(5, 3.f);
	rubik->bindCoordSys(cs1);
}
void WorldDrawer3d::onIdle(){	//per frame
	keyOperations();
	//Sleep(20);

	float step = 1.01f;
	float angle = 0.05f;
	float trans_step = 0.05f;
	static int iteration=1;
	static int dir = 1;
	static int max_iter = 150;
	static float angleRot = 0;
	if(animation){
		

	}

}

void WorldDrawer3d::keyOperations()
{
	if (keyStates[KEY_ESC])
		glutExit();
	
	// Arrow keys rotate the entire cube
	float rotateStep = 2.f;

	if (keySpecialStates[KEY_UP])
	{
		std::cerr << "UP was pressed\n";
		viewAngleY -= rotateStep;
	}
	if (keySpecialStates[KEY_DOWN])
	{
		std::cerr << "DOWN was pressed\n";
		viewAngleY += rotateStep;
	}
	if (keySpecialStates[KEY_LEFT])
	{
		std::cerr << "LEFT was pressed\n";
		viewAngleX -= rotateStep;
	}
	if (keySpecialStates[KEY_RIGHT])
	{
		std::cerr << "RIGHT was pressed\n";
		viewAngleX += rotateStep;
	}

	// Move the cube forwards and backwards
	float eyeDistanceStep = 1.f;

	if (keyStates['['])
	{
		std::cerr << "[ was pressed\n";
		eyeDistance -= eyeDistanceStep;		// Move closer to the viewer
	}
	if (keyStates[']'])
	{
		std::cerr << "] was pressed\n";
		eyeDistance += eyeDistanceStep;		// Move farther from the viewer
	}

	// Rotate faces
	float faceRotateStep = float(M_PI_4 / 24);
	if (keyStates['q'])								// Rotate on X axis, positive
	{
		std::cerr << "q was pressed\n";
		
		rubik->rotateLayerX(rubik->selectedX, faceRotateStep);
	}
	if (keyStates['a'])								// Rotate on X axis, negative
	{
		std::cerr << "a was pressed\n";
		rubik->rotateLayerX(rubik->selectedX, -faceRotateStep);
	}
	if (keyStates['w'])								// Rotate on Y axis, positive
	{
		std::cerr << "w was pressed\n";
		rubik->rotateLayerY(rubik->selectedY, faceRotateStep);
	}
	if (keyStates['s'])								// Rotate on Y axis, negative
	{
		std::cerr << "s was pressed\n";
		rubik->rotateLayerY(rubik->selectedY, -faceRotateStep);
	}
	if (keyStates['e'])								// Rotate on Z axis, positive
	{
		std::cerr << "e was pressed\n";
		rubik->rotateLayerZ(rubik->selectedZ, faceRotateStep);
	}
	if (keyStates['d'])								// Rotate on Z axis, negative
	{
		std::cerr << "d was pressed\n";
		rubik->rotateLayerZ(rubik->selectedZ, -faceRotateStep);
	}

	// Select layers (increase/decrease)
	if (keyStates['t'])
	{
		std::cerr << "t was pressed\n";
		if (!rubik->rotInProgress())
			rubik->increaseSelectedX();
	}
	if (keyStates['g'])
	{
		std::cerr << "g was pressed\n";
		if (!rubik->rotInProgress())
			rubik->decreaseSelectedX();
	}
	if (keyStates['y'])
	{
		std::cerr << "y was pressed\n";
		if (!rubik->rotInProgress())
			rubik->increaseSelectedY();
	}
	if (keyStates['h'])
	{
		std::cerr << "h was pressed\n";
		if (!rubik->rotInProgress())
			rubik->decreaseSelectedY();
	}
	if (keyStates['u'])
	{
		std::cerr << "u was pressed\n";
		if (!rubik->rotInProgress())
			rubik->increaseSelectedZ();
	}
	if (keyStates['j'])
	{
		std::cerr << "j was pressed\n";
		if (!rubik->rotInProgress())
			rubik->decreaseSelectedZ();
	}
}

void WorldDrawer3d::mouseCallbackFunction(int button, int state, int x, int y)
{
	mousePosX = float (x);
	mousePosY = float (y);
	if (button == MOUSE_LEFT)
	{
		if (state == GLUT_DOWN)
			mouseLeftState = true;
		else if (state == GLUT_UP)
			mouseLeftState = false;
	}
	else if (button == MOUSE_RIGHT)
	{
		if (state == GLUT_DOWN)
			mouseRightState = true;
		else if (state == GLUT_UP)
			mouseRightState = false;
	}
}

void WorldDrawer3d::mouseMotionCallbackFunction(int x, int y)
{
	float eyeDistanceStep = 0.2f;
	if (mouseLeftState == true)
	{
		std::cerr << "(" << mousePosX << "," << mousePosY << ") MouseLeft ";
		viewAngleX += (x - mousePosX);
		viewAngleY += (y - mousePosY);
		mousePosX = float(x);
		mousePosY = float(y);
	}
	if (mouseRightState == true)
	{
		std::cerr << "(" << mousePosX << "," << mousePosY << ") MouseRight ";
		eyeDistance -= (y - mousePosY) * eyeDistanceStep;
		mousePosY = float (y);
	}
}


int main(int argc, char** argv){
	WorldDrawer3d wd3d(argc,argv,600,600,200,100,std::string("Tema 2: Rubik Cube"));
	wd3d.init();
	wd3d.run();
	return 0;
}