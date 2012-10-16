#pragma once
#include "support2d.h"

class Circle2d :
	public Object2d
{
public:
	Circle2d();
	Circle2d(float radius);
	~Circle2d();
public:
	float radius;
private:
	void init();
};

