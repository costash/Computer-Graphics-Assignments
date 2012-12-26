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

#define PLAYER_RADIUS 1.f	// Radius for player
#define HALF_CUBE 1.5f		// Size for half of a cube

// Modes for camera
enum CameraModes
{
	MODE_FPS = 1,
	MODE_TPS = 2,
	MODE_TOP = 3
};

// Types for a cell in Maze
enum CellType
{
	PORTAL = 3,
	PLAYER = 2,
	WALL = 1,
	PATH = 0
};