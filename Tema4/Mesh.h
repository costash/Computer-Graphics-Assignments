// Source file for printing ply mesh statistics
#pragma once


////////////////////////////////////////////////////////////
// INCLUDE FILES
////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include "Vector3D.h"


////////////////////////////////////////////////////////////
// TYPE DEFINITIONS
////////////////////////////////////////////////////////////

typedef struct Vertex {
	float x, y, z;
} Vertex;

typedef struct Face {
	Face(void) : nverts(0), verts(0) {};
	int nverts;
	Vertex **verts;
	float normal[3];
} Face;

typedef struct Mesh {
	Mesh(void) : nverts(0), verts(0), nfaces(0), faces(0), center(Vector3D()), radius(0) {};
	int nverts;
	Vertex *verts;
	int nfaces;
	Face *faces;

	Vector3D center;
	float radius;

	// OFF file reading
	int ReadOffFile(const char *filename);

	// Initialize Mesh
	void Init(const char *filename);

	// Compute Mesh Center (and also radius)
	Vector3D computeMeshCenter();

	// Centrate Mesh to (0, 0, 0)
	void centrateMesh();
} Mesh;





////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
////////////////////////////////////////////////////////////

//static char *filename = 0;
//static Mesh *mesh = 0;



////////////////////////////////////////////////////////////
// PLY FILE READING CODE
////////////////////////////////////////////////////////////

void
	PrintStats(Mesh *mesh);