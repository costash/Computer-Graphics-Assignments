#pragma once

#include <freeglut.h>
#include "Object3D.h"

/*
	Clasa Plane
	deseneaza un plan cu numar variabil de quaduri in XOZ
*/

// derivata din Object3D
class Plane : public Object3D
{

// VARIABILE
//-------------------------------------------------
private:
	// dimensiunea unei laturi
	float size;

// FUNCTII
//-------------------------------------------------
public:
	// constructor fara parametri
	Plane();
	// constructor care ia dimensiunea unei laturi
	Plane(float);

protected:
	// functia custmDraw care va fi apelata de Object3D pentru a desena planul
	void customDraw();
};