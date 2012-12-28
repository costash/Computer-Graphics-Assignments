// EGC
// Laborator 7
//-------------------------------------------------


#include "plane.h"

// constructor mostenit din Object3D
// tipul este Custom, pentru a apela customDraw()
Plane::Plane() : Object3D(Custom)
{
	size = 5;
}

// constructor care seteaza in plus si dimensiunea size
Plane::Plane(float _size) : Object3D(Custom)
{
	size = _size;
}

// functie override customDraw(), apelata din Draw()-ul din Object3D
void Plane::customDraw()
{
	glPushMatrix();

	// setari de material
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(Vector4D(color.x * 5,color.y * 5,color.z * 5,1)).Array());
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(Vector4D(0,0,0,0)).Array());
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(Vector4D(0,0,0,0)).Array());

	float leftMargin,rightMargin;

	leftMargin = -size;
	rightMargin = size;

	float i,j;
	float factor = 0.1f;

	// mutare in coordonate
	glTranslatef(translation.x, translation.y, translation.z);
	// colorare corespunzatoare
	glColor3f(color.x, color.y, color.z);

	// desenare plan
	for( i = leftMargin ; i+(levelOfDetail*factor)<=rightMargin; i+=(levelOfDetail*factor))
		for(j=leftMargin;j+(levelOfDetail*factor)<=rightMargin; j+=(levelOfDetail*factor))
		{
			if( !Wireframe)
				glBegin(GL_QUADS);
			else
				glBegin(GL_LINE_LOOP);

			glNormal3f(0.0,1.0,0.0);
			glVertex3f(i ,  0, j);
			glVertex3f(i, 0, j+(levelOfDetail*factor));
			glVertex3f(i+(levelOfDetail*factor), 0, j+(levelOfDetail*factor));
			glVertex3f(i+(levelOfDetail*factor),  0, j);

			glEnd();
		}

	glPopMatrix();
}