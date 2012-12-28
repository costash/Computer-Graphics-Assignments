// EGC
// Laborator 7
//-------------------------------------------------

#include "Object3D.h"

/*
Declaratiile clasei Object3D
Clasa pentru desenare si modificare a unui obiect 3d.
*/

// VARIABILE STATICE
//-------------------------------------------------
//float *Vector3D::arr = new float[3];
Vector3D Object3D::SelectedColor = Vector3D(1,0,1);		// culoarea obiectului selectat
Vector3D Object3D::ColorIncrement = Vector3D(0.04f,0.04f,0.04f);	// valoarea cu care creste/scade in timp culoarea de mai sus


// CONSTRUCTORI
//-------------------------------------------------

// constructor de baza
Object3D::Object3D()
{
	defaultSettings();
}

// seteaza si tipul obiectului
Object3D::Object3D(ObjectType _Type)
{
	defaultSettings();
	Type = _Type;
}

// seteaza si pozitia
Object3D::Object3D(Vector3D *_translation)
{
	defaultSettings();
	this->SetPosition(_translation);
}

// seteaza pozitie, rotatie, translatie
Object3D::Object3D(Vector3D *_translation, Vector3D *_rotation, Vector3D *_scale)
{
	defaultSettings();
	this->SetPosition(_translation);
	this->SetRotation(_rotation);
	this->SetScale(_scale);	
}

// seteaza toti parametrii la valorile lor default
void Object3D::defaultSettings()
{
	translation = Vector3D(0.0,0.0,0.0);
	rotation = Vector3D(0.0,0.0,0.0);
	scale = Vector3D(1.0,1.0,1.0);

	Lighted = true;
	Wireframe = false;
	Visible = true;
	Type = GlutCube;

	levelOfDetail = 12;
	selected = false;
}

// DRAW
//-------------------------------------------------
void Object3D::Draw ()
{
	// daca nu este vizibil, nu-l desenam
	if(!Visible)
	return;

	glPushMatrix();

	// translatie
	glTranslatef( translation.x , translation.y , translation.z );

	// rotatie
	glRotatef( rotation.x , 1.0 , 0.0 , 0.0 );
	glRotatef( rotation.y , 0.0 , 1.0 , 0.0 );
	glRotatef( rotation.z , 0.0 , 0.0 , 1.0 );

	// scalare
	glScalef( scale.x , scale.y , scale.z);

	// setari de material :
	// daca nu este selectat
	if( !selected )
	{
		// culoare normala
		glColor3f(color.x,color.y,color.z);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(Vector4D(color.x,color.y,color.z,1)).Array());
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
		switch( Type )
	{
		// cub wireframe
		case GlutCube :	glutWireCube(1.0f); break;
		// sfera wireframe
		case GlutSphere : glutWireSphere(1.0f, (GLint)levelOfDetail, (GLint)levelOfDetail); break;
		// orice alt obiect, specificat de programator
		case Custom : customDraw();
	}
	// daca nu este wireframe
	else
		switch( Type )
	{
		// cub solid
		case GlutCube :	glutSolidCube(1.0f); break;
		// sfera solida
		case GlutSphere : glutSolidSphere(1.0f, (GLint)levelOfDetail, (GLint)levelOfDetail); break;
		// orice alt obiect, specificat de programator
		case Custom : customDraw();
	}

	glPopMatrix();
}

// functie proprie
// se presupune ca Wireframe este tratat inauntru
void Object3D::customDraw()
{
	// TODO : aici va puteti desena un obiect personalizat/incarcat din fisier/pre-generat/etc
}

// SETTERS
//-------------------------------------------------

// selecteaza
void Object3D::Select()
{
	selected = true;
}

// deselecteaza
void Object3D::Deselect()
{
	selected = false;
}

// seteaza culoare
void Object3D::SetColor(Vector3D *_color)
{
	color = *_color;
}

// seteaza pozitie
void Object3D::SetPosition(Vector3D *_translation)
{
	translation = *_translation;
}

// seteaza rotatie
void Object3D::SetRotation(Vector3D *_rotation)
{
	rotation = *_rotation;
}

// seteaza scalare
void Object3D::SetScale(Vector3D *_scale)
{
	scale = *_scale;
}

// seteaza nivelul de detaliu
void Object3D::SetLevelOfDetail(float _levelOfDetail)
{
	if( _levelOfDetail > 0 && _levelOfDetail < MAXIMUM_LOD)
		levelOfDetail = _levelOfDetail;
}


// GETTERS
//-------------------------------------------------

// intoarce pozitia
Vector3D Object3D::GetPosition()
{
	return translation;
}

// intoarce rotatia
Vector3D Object3D::GetRotation()
{
	return rotation;
}

// intoarce scala
Vector3D Object3D::GetScale()
{
	return scale;
}

// intoarce nivelul de detaliu
float Object3D::GetLevelOfDetail()
{
	return levelOfDetail;
}
