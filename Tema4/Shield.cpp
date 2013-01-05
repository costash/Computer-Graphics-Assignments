#include "Shield.h"

Shield::Shield(CustomObject3D *aircraft)
	: alpha(0), aircraft(aircraft), draw(true)
{
}

Shield::Shield(float alpha, CustomObject3D *aircraft)
	: alpha(alpha), aircraft(aircraft), draw(true)
{
}

Shield::~Shield()
{
}

void Shield::Draw()
{
	if (draw)
	{
		glPushMatrix();
		Vector3D pos = aircraft->GetPosition();
		glTranslatef(pos.x, pos.y, pos.z);

		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(Vector4D(0.8f, 0.8f, 0.8f, alpha)).Array());
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(Vector4D(0.1f,0.1f,0.1f,1.f)).Array());
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

		glutSolidSphere(aircraft->getRadius(), 100, 100);

		glPopMatrix();
	}
}

void Shield::setAlpha(float alpha)
{
	this->alpha = alpha;
}

float Shield::getAlpha()
{
	return alpha;
}

void Shield::incrementAlpha(float step)
{
	alpha += step;
	if (alpha > 1)
		alpha = 1;
}

void Shield::decrementAlpha(float step)
{
	alpha -= step;
	if (alpha < 0)
		alpha = 0;
}