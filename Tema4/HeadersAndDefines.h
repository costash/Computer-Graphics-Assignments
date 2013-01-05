#pragma once
#define _USE_MATH_DEFINES		// Used to activate PI related constants
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "glut\freeglut.h"
#include <iostream>

#define KEY_DOWN GLUT_KEY_DOWN
#define KEY_LEFT GLUT_KEY_LEFT
#define KEY_UP GLUT_KEY_UP
#define KEY_RIGHT GLUT_KEY_RIGHT
#define KEY_ESC 27
#define KEY_SPACE 32

#define MOUSE_LEFT GLUT_LEFT_BUTTON
#define MOUSE_MIDDLE GLUT_MIDDLE_BUTTON
#define MOUSE_RIGHT GLUT_RIGHT_BUTTON

#define ANGLE_LIMIT (M_PI_2 - 0.1f)	// Angle limit for rotation around OX

#define PLAYER_RADIUS 0.25f	// Radius for player
#define HALF_CUBE 1.5f		// Size for half of a cube
#define PLANE_SIZE 200.f	// Size of a plane

#define NUM_ASTEROIDS 150	// Number of asteroids
#define NUM_WRENCHES 10		// Number of wrenches

#define SHIELD_STEP 0.1f	// Step for the shield to be modified

#define AIRCRAFT 1			// ID for aircraft call list
#define ASTEROID 2			// ID for asteroid call list
#define WRENCH 3			// ID for wrench call list