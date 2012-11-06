#pragma once
#include "HeadersAndDefines.h"
#include "Support3d.h"

namespace WorldDrawer3dNamespace
{
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

	public:
		static bool animation;
		static CoordinateSystem3d cs_basis;
		static std::vector<CoordinateSystem3d*> cs_used;
		static bool keyStates[256];
		static bool keySpecialStates[256];
	};
}