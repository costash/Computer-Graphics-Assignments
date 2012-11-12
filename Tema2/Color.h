#pragma once

//-----------------------------------------------------------------------------------------------------
//	RGB Color class. Holds a tuple for red, green and blue
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

