#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include "dependinte\freeglut.h"
#include <iostream>
#include "Support3d.h"
#include "Color.h"

#define KEY_DOWN GLUT_KEY_DOWN
#define KEY_LEFT GLUT_KEY_LEFT
#define KEY_UP GLUT_KEY_UP
#define KEY_RIGHT GLUT_KEY_RIGHT
#define KEY_ESC 27
#define KEY_SPACE 32

#define MOUSE_LEFT GLUT_LEFT_BUTTON
#define MOUSE_MIDDLE GLUT_MIDDLE_BUTTON
#define MOUSE_RIGHT GLUT_RIGHT_BUTTON

static Color rubik_colors[6] =
{ 
	Color(1, 1, 0),		// Top color
	Color(1, 1, 1),		// Bottom color
	Color(1, 0.5f, 0),	// Left color
	Color(1, 0, 0),		// Right color
	Color(0, 0, 1),		// Front color
	Color(0, 1, 0)		// Back color
};