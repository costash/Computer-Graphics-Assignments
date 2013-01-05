#pragma once
#include "Vector3D.h"
#include "Vector4D.h"
#include "CustomObject3D.h"

class Shield
{
public:

	Shield(CustomObject3D *aircraft);
	Shield(float alpha, CustomObject3D *aircraft);

	~Shield();

	void Draw();

	void setAlpha(float alpha);
	float getAlpha();
	void incrementAlpha(float step);
	void decrementAlpha(float step);

	inline void enable()
	{
		draw = true;
	}
	void disable()
	{
		draw = false;
	}

private:
	float alpha;
	CustomObject3D *aircraft;
	bool draw;
};

