#pragma once
#include "customobject3d.h"
class Asteroid :
	public CustomObject3D
{
public:
	Asteroid(Mesh *mesh, int id, bool firstObject);
	virtual ~Asteroid();

public:
	// Overridden Draw
	void Draw();

private:
	int callListId;
	bool callListRecreated;
	bool firstObject;

public:
	float moveStep;
	Vector3D angleStep;
};

