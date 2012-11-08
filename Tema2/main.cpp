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

using namespace WorldDrawer3dNamespace;

bool WorldDrawer3d::animation=true;
bool WorldDrawer3d::keyStates[256];
bool WorldDrawer3d::keySpecialStates[256];


//used global vars
CoordinateSystem3d *cs1;
Object3d *o1, *o2, *o3, *o4,*o5, *o6;

Rubik *rubik;

//add
void WorldDrawer3d::init(){
	//creeaza 2 sistem de coordonate client
	cs1 = new CoordinateSystem3d();
	cs_used.push_back(cs1);
	
	//cub
	//std::vector<Point3d> points;
	//std::vector<int> topology;
	//points.push_back(Point3d(1,1,1));
	//points.push_back(Point3d(1,1,-1));
	//points.push_back(Point3d(-1,1,-1));
	//points.push_back(Point3d(-1,1,1));
	//points.push_back(Point3d(1,-1,1));
	//points.push_back(Point3d(1,-1,-1));
	//points.push_back(Point3d(-1,-1,-1));
	//points.push_back(Point3d(-1,-1,1));
	//topology.push_back(0);topology.push_back(1);topology.push_back(2);	//top
	//topology.push_back(2);topology.push_back(3);topology.push_back(0);
	//topology.push_back(6);topology.push_back(5);topology.push_back(4);	//bottom
	//topology.push_back(7);topology.push_back(4);topology.push_back(6);
	//topology.push_back(2);topology.push_back(3);topology.push_back(6);	//left
	//topology.push_back(7);topology.push_back(3);topology.push_back(6);
	//topology.push_back(0);topology.push_back(1);topology.push_back(5);	//right
	//topology.push_back(0);topology.push_back(5);topology.push_back(4);
	//topology.push_back(0);topology.push_back(3);topology.push_back(4);	//front
	//topology.push_back(7);topology.push_back(3);topology.push_back(4);
	//topology.push_back(5);topology.push_back(1);topology.push_back(2);	//back
	//topology.push_back(6);topology.push_back(2);topology.push_back(5);
	//o1 = new Object3d(points,topology);
	//o1->setcolor(1,0.8f,0.9f);
	//o1->scaleRelativeToPoint(o1->axiscenter, 2, 4, 2);
	////cs1
	//cs1->objectAdd(o1);
	/*cs1->translate(10,-3,-10);
	cs1->rotateXSelf(3.1416f);*/

	
	//Color colors[6] = { Color(1, 0, 0), Color(0, 1, 1), Color(0, 1, 0), Color(1, 0, 1), Color(0, 0, 1), Color(1, 1, 0) };
	/*o2 = new Cube(6, colors);
	o2->setcolor(1.f, 0.4f, 0.f);
	o2->translate(5.f, 0.f, 0.f);
	o2->rotateYSelf(M_PI_4);
	o2->rotateXSelf(M_PI_4);
	
	o2->rotateXSelf(-M_PI_4);
	o2->rotateYSelf(-M_PI_4);
	cs1->objectAdd(o2);*/
	
	rubik = new Rubik(5, 3.f);
	rubik->bindCoordSys(cs1);
}
void WorldDrawer3d::onIdle(){	//per frame
	keyOperations();
	Sleep(20);

	float step = 1.01f;
	float angle = 0.05f;
	float trans_step = 0.05f;
	static int iteration=1;
	static int dir = 1;
	static int max_iter = 150;
	if(animation){
		
		/*if (iteration < max_iter)
		{
			if (dir == 1)
			{
				o1->scaleRelativeToPoint(o1->axiscenter, step - .01, step - .01, step - .01);
			}
			else
			{
				o1->scaleRelativeToPoint(o1->axiscenter, 1/(step - .01), 1/(step - .01), 1/(step - .01));
			}
			o1->rotateXSelf(dir * angle);
		}

		iteration += dir;
		if (iteration == max_iter || iteration == 0)
			dir *= -1;*/
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
		eyeDistance -= eyeDistanceStep;
	}
	if (keyStates[']'])
	{
		std::cerr << "] was pressed\n";
		eyeDistance += eyeDistanceStep;
	}

	// Letters
	if (keyStates['e'])
		std::cerr << "e was pressed\n";

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