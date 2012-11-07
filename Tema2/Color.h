#pragma once

//-----------------------------------------------------------------------------------------------------
//	RGB Color class
//-----------------------------------------------------------------------------------------------------

class Color
{
public:
	Color();
	Color(float r, float g, float b);
	~Color();
public:
	float r;	// red
	float g;	// green
	float b;	// blue
};

