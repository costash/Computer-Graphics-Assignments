#pragma once

#include <freeglut.h>
#include "Vector3D.h"
#include "Vector4D.h"

// nivelul maxim de detaliu
#define MAXIMUM_LOD 50 

enum ObjectType
{
	GlutCube,	// glut cube
	GlutSphere, // glut sphere
	Custom  // obiect propriu
};

/*
	OBJECT3D
	Clasa pentru desenare si modificare a unui obiect 3d.
*/
class Object3D
{
// VARIABILE STATICE ::
//-------------------------------------------------
public:
	static Vector3D SelectedColor;
	static Vector3D ColorIncrement;

// VARIABILE
//-------------------------------------------------
// publice
public :
	// incep cu litera mare
	ObjectType Type;	// tipul obiectuliu
	bool Wireframe;		// daca va fi desenat wireframe
	bool Visible;		// daca va fi sau nu desenat
	bool Lighted;		// daca este sau nu luminat

// private
protected:
	// incep cu litera mica
	Vector3D translation;	// pozitie
	Vector3D rotation;		// rotatie
	Vector3D scale;			// scalare
	Vector3D color;			// culoare

	float levelOfDetail;	// nivelul de detaliu (pentru glutSphere)
	bool selected;			// daca este sau nu selectat


// FUNCTII ::
//-------------------------------------------------
public:
// constructor
	// fara parametri
	Object3D();		
	// doar cu tip
	Object3D(ObjectType);
	// doar cu pozitie
	Object3D(Vector3D *);			
	// cu pozitie, rotatie, scalare
	Object3D(Vector3D *,Vector3D *,Vector3D *);

// functie de desenare
	void virtual Draw();

// setters 
	// pentru toate variabilele care nu sunt publice
	void Select();
	void Deselect();
	void SetPosition(Vector3D *);
	void SetRotation(Vector3D *);
	void SetScale(Vector3D *);
	void SetColor(Vector3D *);
	void SetLevelOfDetail(float);
// getters
	// pentru toate variabilele care nu sunt publice, si pot fi modificate din exterior
	Vector3D GetRotation();
	Vector3D GetScale();
	Vector3D GetPosition();
	float GetLevelOfDetail();

protected:
	// functie proprie de desenare. se apeleaza doar daca tipul este Custom
	void virtual customDraw();
	// seteaza valorile default 
	void defaultSettings();
	
};