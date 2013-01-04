#include "Asteroid.h"


Asteroid::Asteroid(Mesh *mesh, int id, bool firstObject)
	: CustomObject3D(mesh), callListId(id), callListRecreated(false), firstObject(firstObject),
	moveStep(0), angleStep(Vector3D())
{
}


Asteroid::~Asteroid()
{
}

void Asteroid::Draw()
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

	if (firstObject && !callListRecreated)
	{
		callListRecreated = true;
		glNewList(callListId, GL_COMPILE);
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
		glEndList();
	}
	else
	{
		glCallList(callListId);
	}
	glPopMatrix();
}