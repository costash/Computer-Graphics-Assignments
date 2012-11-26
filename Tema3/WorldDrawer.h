#pragma once
#include "HeadersAndDefines.h"
#include "Vector3D.h"
#include "camera.h"

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

	// Text drawing helpers
	//static void drawText(float posx, float posy, float posz, Color col, const unsigned char * text);

public:
	static bool animation;
	static bool keyStates[256];					// Key Buffer for standard keys
	static bool keySpecialStates[256];			// Key Buffer for special keys
	static bool mouseLeftState;					// Left mouse button state
	static bool mouseRightState;				// Right mouse button state
	static float mousePosX, mousePosY;			// Mouse position
	static float viewAngleX, viewAngleY;		// View angle
	static float eyeDistance;					// View distance
	static unsigned int tick;					// Used for clock

	static int mainWindow;						// The ID for mainWindow created by GLUT
	static bool windowCreated;					// Wether a new window has been created or not
	static int secondaryWindow;					// The ID for a secondary window

	static Camera camera;
	static float angle;
};