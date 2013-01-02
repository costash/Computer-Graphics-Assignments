#pragma once
#include "HeadersAndDefines.h"
#include "Vector3D.h"
#include "camera.h"


#include "Cube.h"
#include "Light.h"
#include "Plane.h"
#include "CustomObject3D.h"

class WorldDrawer{
public:
	WorldDrawer(int argc, char **argv, int windowWidth, int windowHeight,
		int windowStartX, int windowStartY, std::string windowName);
	~WorldDrawer();
	static void run();	
	static void displayCallbackFunction();
	static void reshapeCallbackFunction(int width, int height);
	static void idleCallbackFunction();
	static void keyboardCallbackFunction(unsigned char key, int x, int y);
	static void keyboardSpecialCallbackFunction(int key, int x, int y);


	//implemented in main
	static void init();
	static void onIdle();

	// Keyboard callbacks implemented in WorldDrawer
	static void keyDownCallbackFunction(unsigned char key, int posx, int posy);
	static void keyUpCallbackFunction(unsigned char key, int posx, int posy);
	static void specialKeyDownCallbackFunction(int key, int posx, int posy);
	static void specialKeyUpCallbackFunction(int key, int posx, int posy);

	// Keyboard operations logic
	static void keyOperations();

	// Mouse callbacks
	static void mouseCallbackFunction(int button, int state, int x, int y);
	static void mouseMotionCallbackFunction(int x, int y);
	static void mouseWheelCallbackFunction(int wheel, int direction, int x, int y);

	// Timer helpers
	static unsigned int getTimeDifference();
	static unsigned int getTime();

	// Mouse rotations helper
	static void mouseRotations();
	static void switchCameraMode(int mode);
	static Vector3D getPlayerPosition();

	// Draw main axis
	static void drawAxis();

	// Init display lists
	static void initDisplayLists();

public:
	static bool animation;
	static bool keyStates[256];					// Key Buffer for standard keys
	static bool keySpecialStates[256];			// Key Buffer for special keys
	static bool mouseLeftState;					// Left mouse button state
	static bool mouseRightState;				// Right mouse button state
	static float mousePosX, mousePosY;			// Mouse position
	static float viewAngleX, viewAngleY;		// View angle for FPS
	static float viewAngleTpsX, viewAngleTpsY;	// View angle for TPS
	static float eyeDistance;					// View distance
	static unsigned int tick;					// Used for clock

	static int mainWindow;						// The ID for mainWindow created by GLUT
	static bool windowCreated;					// Wether a new window has been created or not
	static int secondaryWindow;					// The ID for a secondary window

	static Camera camera;						// Camera
	static float distanceToTPSTarget;			// Distance to the target for TPS camera
	static float distanceToTop;					// Distance to Top camera
	static float mouseSensivity;				// Mouse sensivity
	static float zoomSensivity;					// Sensivity for zooming with scroll

	static float angle;							// Angle for cubes rotating


	static CustomObject3D *aircraft;			// Aircraft object
	static Object3D *gameBox;					// The box surrounding the game
	static Mesh *aircraftMesh;					// Mesh for aircraft
	static Mesh *asteroidMesh;					// Mesh for asteroid
	// Omnidirectional light
	static Light *light_o;
};