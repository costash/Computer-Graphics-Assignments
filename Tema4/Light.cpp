// EGC
// Laborator 7
//-------------------------------------------------

#include "Light.h"

// id-ul de baza
int Light::baseId = 0;

// constructor fara parametri, mosteneste constructorul de Sfera din Object3D
// deoarece dorim ca lumina sa fie ilustrata printr-o sfera
Light::Light() : Object3D(GlutSphere)
{
	// valori default
	diffuse = Vector4D(4,4,4,1);
	ambient = Vector4D(0,0,0,0);
	specular = Vector4D(1,1,1,1);
	color = Vector3D(1,1,1);
	scale = Vector3D(0.2f,0.2f,0.2f);

	// id-ul este unic, id-ul de baza incrementat
	id = baseId++;
	
	// sfera plasata in locul luminii nu este wireframe
	Wireframe = false;

	// default lumina este omnidirectionala
	LightType = IlluminationType::Ideal;
}

// seteaza tipul de lumina
void Light::SetLightType(IlluminationType _LightType)
{
	LightType  = _LightType;
}

// functie care plaseaza efectivl umina in scena
void Light::Render()
{
	// atenuari standard
	glLightf(GL_LIGHT0 + id,GL_CONSTANT_ATTENUATION,1);
	glLightf(GL_LIGHT0 + id,GL_LINEAR_ATTENUATION,0.2f);

	// culoarea luminii 
	glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, Vector4D(diffuse.x, diffuse.y, diffuse.z, diffuse.a).Array());
	// culoarea ambientala 
	glLightfv(GL_LIGHT0 + id, GL_AMBIENT, ambient.Array());
	// culoarea speculara
	glLightfv(GL_LIGHT0 + id, GL_SPECULAR, specular.Array());
	// pozitia luminii
	glLightfv(GL_LIGHT0 + id, GL_POSITION, Vector4D(translation.x,translation.y,translation.z,1).Array());

	// daca este de tip spot , setam parametrii de spot ( se vor folosi valori default )
	if(LightType == IlluminationType::Spot)
	{
		// directia spotului va fi in jos
		glLightfv(GL_LIGHT0 + id , GL_SPOT_DIRECTION, (Vector3D(0.0,-1.0,0.0)).Array());      
		// deschidere de 45 de grade
		glLightf(GL_LIGHT0 + id , GL_SPOT_CUTOFF, 45.0);
		glLightf(GL_LIGHT0 + id , GL_SPOT_EXPONENT, 2);
	}

	// activam lumina
	glEnable(GL_LIGHT0 + id);
}

// functie care dezactiveaza lumina
void Light::Disable()
{
	glDisable(GL_LIGHT0 + id);
}
