#include "CustomObject3D.h"

// Constructor
CustomObject3D::CustomObject3D(Mesh *mesh)
	: mesh(mesh), meshCenter(0.f, 0.f, 0.f), callListId(-1), createdCallList(false)
{
	setDefault();
}

CustomObject3D::CustomObject3D(Mesh *mesh, int id)
	: mesh(mesh), meshCenter(0.f, 0.f, 0.f), callListId(id), createdCallList(false)
{
	setDefault();
}

// Destructor
CustomObject3D::~CustomObject3D()
{
}

void CustomObject3D::setDefault()
{
	// Default lighting
	diffuse = Vector4D(1,1,1,1);
	ambient = Vector4D(0,0,0,0);
	specular = Vector4D(1,1,1,1);
	color = Vector3D(1,1,1);
	scale = Vector3D(1.0,1.0,1.0);

	// Default, it's not wireframe
	Wireframe = false;
}

// Sets diffuse color (alpha test uses A value from diffuse)
void CustomObject3D::SetDiffuse(Vector4D *color)
{
	diffuse = *color;
}

// Computers Mesh center
Vector3D CustomObject3D::computeMeshCenter()
{
	Vector3D center;
	// Compute bounding box
	float xmin = 1.0E30f, ymin = 1.0E30f, zmin = 1.0E30f;
	float xmax = -1.0E30f, ymax = -1.0E30f, zmax = -1.0E30f;
	for (int i = 0; i < mesh->nverts; ++i)
	{
		Vertex& v = mesh->verts[i];
		if (v.x < xmin) xmin = v.x;
		if (v.y < ymin) ymin = v.y;
		if (v.z < zmin) zmin = v.z;
		if (v.x > xmax) xmax = v.x;
		if (v.y > ymax) ymax = v.y;
		if (v.z > zmax) zmax = v.z;
	}
	center.x = (xmax - xmin) / 2;
	center.y = (ymax - ymin) / 2;
	center.z = (zmax - zmin) / 2;
	return center;
}

// Return object radius
float CustomObject3D::getRadius()
{
	return mesh->radius * scale.x;
}

// Overridden Draw
void CustomObject3D::Draw()
{
	// Object is not visible
	if (!Visible)
		return;

	glPushMatrix();

	// Translation
	glTranslatef( translation.x , translation.y , translation.z );

	// Rotation
	glRotatef( rotation.x , 1.0 , 0.0 , 0.0 );
	glRotatef( rotation.y , 0.0 , 1.0 , 0.0 );
	glRotatef( rotation.z , 0.0 , 0.0 , 1.0 );

	// Scale
	glScalef( scale.x , scale.y , scale.z);

	// Material settings :
	// If not selected
	if( !selected )
	{
		// Normal color
		glColor3f(color.x,color.y,color.z);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(Vector4D(diffuse.x,diffuse.y,diffuse.z,diffuse.a)).Array());
	}
	else
	{
		// culoarea atunci cand obiectul este selectat
		glColor3f(SelectedColor.x, SelectedColor.y, SelectedColor.z);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(Vector4D(SelectedColor.x,SelectedColor.y,SelectedColor.z,1)).Array());
	}
	// culoare speculara, default
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(Vector4D(0.1f,0.1f,0.1f,1.f)).Array());

	// daca este wireframe
	if( Wireframe )
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
	// daca nu este wireframe
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}

	if (callListId > -1)
	{
		if (createdCallList == false)
		{
			glNewList(callListId, GL_COMPILE_AND_EXECUTE);
			customDraw();
			glEndList();
			createdCallList = true;
		}
		else
		{
			glCallList(callListId);
		}
	}
	else
		customDraw();

	glPopMatrix();
}

void CustomObject3D::customDraw()
{
	// Draw each face
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < mesh->nfaces; ++i)
	{
		/*glNormal3f(mesh->faces[i].normal[0], mesh->faces[i].normal[1], mesh->faces[i].normal[2]);*/
		for (int j = 0; j < mesh->faces[i].nverts; ++j)
		{
			Vertex *vert = mesh->faces[i].verts[j];
			glNormal3f(mesh->faces[i].normal[0], mesh->faces[i].normal[1], mesh->faces[i].normal[2]);
			glVertex3f(vert->x, vert->y, vert->z);
		}


	}
	glEnd();
}