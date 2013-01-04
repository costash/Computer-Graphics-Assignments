#pragma once
#include "Object3d.h"
#include "Mesh.h"
#include "Vector3D.h"

class CustomObject3D : public Object3D
{
public:
	// Constructor default
	CustomObject3D(Mesh *mesh);
	// Constructor with callList
	CustomObject3D(Mesh *mesh, int id);

	// Destructor
	virtual ~CustomObject3D();

	// Overridden Draw
	void Draw();

	// Sets diffuse color (alpha test uses A value from diffuse)
	void SetDiffuse(Vector4D *color);

	// Return object radius
	float getRadius();

protected:
	// Computers Mesh center
	Vector3D computeMeshCenter();
	// Custom draw method
	void customDraw();
	// Sets default settings for a custom object
	void setDefault();

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

	// CallList id (it should be -1 if not using callLists)
	int callListId;
	// Has created the callList
	bool createdCallList;
};
