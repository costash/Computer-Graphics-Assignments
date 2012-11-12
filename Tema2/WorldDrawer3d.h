#pragma once
#include "HeadersAndDefines.h"
#include "Support3d.h"

class WorldDrawer3d{
public:
	//implemented in worldDrawer3d_gl
	WorldDrawer3d(int argc, char **argv, int windowWidth, int windowHeight,
		int windowStartX, int windowStartY, std::string windowName);
	~WorldDrawer3d();
	static void run();	
	static void displayCallbackFunction();
	static void reshapeCallbackFunction(int width, int height);
	static void idleCallbackFunction();
	static void keyboardCallbackFunction(unsigned char key, int x, int y);
	static void keyboardSpecialCallbackFunction(int key, int x, int y);


	//implemented in worldDrawer3d_logic (main)
	static void init();
	static void onIdle();

	// Keyboard callbacks implemented in WorldDrawer3d_gl
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

	static unsigned int getTimeDifference();
	static unsigned int getTime();

	static void drawText(float posx, float posy, float posz, Color col, const unsigned char * text);
	static void drawScore(float posx, float posy, float posz, Color col);
	static void drawWin(float posx, float posy, float posz, Color col);

public:
	static bool animation;
	static CoordinateSystem3d cs_basis;
	static std::vector<CoordinateSystem3d*> cs_used;
	static bool keyStates[256];					// Key Buffer for standard keys
	static bool keySpecialStates[256];			// Key Buffer for special keys
	static bool mouseLeftState;					// Left mouse button state
	static bool mouseRightState;				// Right mouse button state
	static float mousePosX, mousePosY;			// Mouse position
	static float viewAngleX, viewAngleY;		// View angle
	static float eyeDistance;					// View distance
	static unsigned int tick;					// Used for clock

	static int mainWindow;
	static bool windowCreated;
	static int secondaryWindow;
};