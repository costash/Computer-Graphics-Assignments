//-----------------------------------------------------------------------------------------------
//					Tema1
//
//	Fisiere de interes: Transform2d.cpp main.cpp
//
//	Functii WorldDrawer2d:
//	-init e apelat o singura data, la inceput.
//	-idle e apelat per cadru de desenare
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

#include "WorldDrawer2d.h"
#include "Circle2d.h"
#include "Rectangle2d.h"
#include <iostream>
bool WorldDrawer2d::animation=true;


//used global vars
CoordinateSystem2d *cs1, *cs2,*cs3;
Object2d *o1, *o2, *o3;
Circle2d *circle1, *circle2;
Object2d *out_border, *in_border;
Object2d *out_net1, *in_net1, *out_net2, *in_net2;
Object2d *net_line1, *net_line2, *board_center_line;

// Constants
const float out_length = 22.5f;
const float out_height = 28.f;
const float out_small_length = 22.f;
const float out_small_heigth = 27.5f;
const float net_outer_length = 8.f;
const float net_outer_heigth = 5.f;
const float net_inner_length = 7.5f;
const float net_inner_height = 4.5f;
const float net_translate_y = 14.f;
const float net_line_length = 7.5f;
const float net_line_height = 0.25f;
const float net_line_translate_y = 13.875f;
const float center_line_height = 0.25f;
const float center_line_length = 22.f;

//add
void WorldDrawer2d::init(){
	//creeaza 2 sistem de coordonate client
	cs1 = new CoordinateSystem2d();
	cs2 = new CoordinateSystem2d();	
	cs3 = new CoordinateSystem2d();
	cs_used.push_back(cs1);
	cs_used.push_back(cs2);
	cs_used.push_back(cs3);
	/*
	//(triunghi rosu)
	std::vector<Point2d> points;
	std::vector<int> topology;
	points.push_back(Point2d(1,0));
	points.push_back(Point2d(-1,0));
	points.push_back(Point2d(0,1));
	topology.push_back(0);
	topology.push_back(1);
	topology.push_back(2);
	o1 = new Object2d(points,topology);
	o1->setcolor(1,0.8f,0.85f);
	//cs 1
	cs1->objectAdd(o1);
	cs1->translate(-5,5);
	cs1->rotateSelf(0.5);

	//(patrat albastru = 2 triunghiuri)	
	o2 = new Rectangle2d(2, 1);
	o2->setcolor(0,0,1);
	o2->translate(0, 1);
	//cs 2
	cs2->objectAdd(o2);
	cs2->translate(-10,-10);
	cs2->rotateSelf(-0.5);
	cs2->objectTranslate(o2,0,5);

	//cerc test maro
	circle1 = new Circle2d(10);
	circle1->scale(1.5);
	circle1->scale(0.15);
	circle1->setcolor(0.5, 0.4, 0.4);
	cs2->objectAdd(circle1);
	cs2->translate(0, 2);

	//cerc unitate
	circle2 = new Circle2d();
	circle2->setcolor(0.1, 0.2, 0.2);
	//circle2->translate(2, 3);
	cs2->objectAdd(circle2);
	cs2->objectTranslate(circle2, -3, 4);

	//dreptunghi în centru
	Object2d *rect1 = new Rectangle2d(2, 4);
	rect1->setcolor(1, 1, 0);
	cs2->objectAdd(rect1);
	cs2->objectTranslate(rect1, 14, 0);
	*/
	// Mingea rosie
	Object2d *ball = new Circle2d(0.5);
	ball->setcolor(1, 0, 0);
	cs1->objectAdd(ball);


	initBoard();
}

void WorldDrawer2d::initBoard()
{
	// Dreptunghi alb la mijlocul terenului
	board_center_line = new Rectangle2d(center_line_length, center_line_height);
	board_center_line->setcolor(1, 1, 1);
	cs1->objectAdd(board_center_line);

	// Dreptunghi alb linia portii de sus
	net_line1 = new Rectangle2d(net_line_length, net_line_height);
	net_line1->setcolor(1, 1, 1);
	net_line1->translate(0, net_line_translate_y);
	cs1->objectAdd(net_line1);

	// Dreptunghi alb linia portii de jos
	net_line2 = new Rectangle2d(net_line_length, net_line_height);
	net_line2->setcolor(1, 1, 1);
	net_line2->translate(0, -net_line_translate_y);
	cs1->objectAdd(net_line2);

	// Dreptunghi portocaliu la interior, teren de joc
	in_border = new Rectangle2d(out_small_length, out_small_heigth);
	in_border->setcolor(1, 0.5, 0);
	cs1->objectAdd(in_border);

	// Dreptunghi portocaliu interiorul portii de sus
	in_net1 = new Rectangle2d(net_inner_length, net_inner_height);
	in_net1->setcolor(1, 0.5, 0);
	in_net1->translate(0, net_translate_y);
	cs1->objectAdd(in_net1);

	// Dreptunghi rosu exterior portii de sus
	out_net1 = new Rectangle2d(net_outer_length, net_outer_heigth);
	out_net1->setcolor(1, 0, 0);
	out_net1->translate(0, net_translate_y);
	cs1->objectAdd(out_net1);

	// Dreptunghi portocaliu interiorul portii de jos
	in_net2 = new Rectangle2d(net_inner_length, net_inner_height);
	in_net2->setcolor(1, 0.5, 0);
	in_net2->translate(0, -net_translate_y);
	cs1->objectAdd(in_net2);

	// Dreptunghi rosu exterior portii de sus
	out_net2 = new Rectangle2d(net_outer_length, net_outer_heigth);
	out_net2->setcolor(1, 0, 0);
	out_net2->translate(0, -net_translate_y);
	cs1->objectAdd(out_net2);

	// Dreptunghi rosu la exterior, manta
	out_border = new Rectangle2d(out_length, out_height);
	out_border->setcolor(1, 0, 0);
	cs1->objectAdd(out_border);
}

void WorldDrawer2d::onIdle(){	//per frame
	//Sleep(25);
	static int iteration=1;
	static bool o1dir=true;
	static bool o2dir=true;
	static bool o3dir=true;
	static bool o3dir2=true;
	static int dir = 1;
	if(animation){
		if (iteration%30 == 0)
			dir *= -1;

		/*o1->translate(dir, 0);

		o2->rotateSelf(0.1);
		o2->rotateRelativeToPoint(cs2->axiscenter, 0.1);
		o2->translate(0.5, 0.5);*/

		iteration++;
	}
}

void WorldDrawer2d::onKey(unsigned char key){
	switch(key){
		case KEY_UP:
			break;
		case KEY_DOWN:
			break;
		case KEY_LEFT:
			break;
		case KEY_RIGHT:
			break;
		case KEY_SPACE:
				animation=!animation;
			break;
		default:
			break;
	}
}


int main(int argc, char** argv){
	WorldDrawer2d wd2d(argc,argv,600,600,200,100,std::string("Tema 1"));
	wd2d.init();
	wd2d.run();
	return 0;
}