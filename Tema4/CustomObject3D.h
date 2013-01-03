#pragma once
#include "Object3d.h"
#include "Mesh.h"
#include "Vector3D.h"

class CustomObject3D : public Object3D
{
public:
	// Constructor
	CustomObject3D(Mesh *mesh);

	// Destructor
	virtual ~CustomObject3D();

	// Overridden Draw
	void Draw();

	// Sets diffuse color (alpha test uses A value from diffuse)
	void SetDiffuse(Vector4D *color);

protected:
	// Computers Mesh center
	Vector3D computeMeshCenter();

protected:
	// Object mesh
	Mesh *mesh;
	// Bounding Box Center
	Vector3D meshCenter;

	// Diffuse color
	Vector4D diffuse;
	// Ambient color
	Vector4D ambient;
	// Specular color
	Vector4D specular;
};
