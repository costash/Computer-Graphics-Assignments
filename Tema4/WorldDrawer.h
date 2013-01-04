#pragma once
#include "HeadersAndDefines.h"
#include "Vector3D.h"
#include "camera.h"
#include <vector>


#include "Cube.h"
#include "Light.h"
#include "Plane.h"
#include "CustomObject3D.h"
#include "Asteroid.h"

// Game camera types
enum CameraRenderType {
	Dynamic,	// Free roam camera
	OnBoard,	// Camera from aircraft
	OnAsteroid	// Camera from asteroid
};

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
	static void switchCameraMode(int mode, Camera &camera);
	static Vector3D getPlayerPosition();

	// Draw main axis
	static void drawAxis();

	// Random helper
	static float genRandomFloat(float min, float max);
	// Random Asteroid position
	static Vector3D genRandomPosition(float minY, float maxY, float minZ, float maxZ);

	// Picking
	// functie ce realizeaza picking la pozitia la care s-a dat click cu mouse-ul
	static void pick(int x, int y);
	// functia care proceseaza hitrecordurile pentru a vedea daca s-a click pe un obiect din scena
	static void processhits (GLint hits, GLuint buffer[]);

	// Draw 3D scene
	static void drawScene();
	// Init scene
	static void initScene();
	// Render Asteroid Camera
	static void asteroidCameraRender(Asteroid *asteroid, Vector3D *target);

	// Checks for collision between two objects
	static bool objectToObjectCollision(CustomObject3D *obj1, CustomObject3D *obj2);
	// Collision logic
	static void collision();

	// Update light position
	static void updateLight();
	// Draw shield
	static void drawShield(float alpha);

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

	static Camera cameraDynamic;				// Dynamic camera
	static Camera cameraOnBoard;				// Onboard camera
	static float distanceToTPSTarget;			// Distance to the target for TPS camera
	static float distanceToTop;					// Distance to Top camera
	static float mouseSensivity;				// Mouse sensivity
	static float zoomSensivity;					// Sensivity for zooming with scroll

	static float angle;							// Angle for cubes rotating


	static CustomObject3D *aircraft;			// Aircraft object
	static Object3D *gameBox;					// The box surrounding the game
	static Mesh *aircraftMesh;					// Mesh for aircraft
	static Mesh *asteroidMesh;					// Mesh for asteroid
	//static CustomObject3D *asteroids;			// Asteroids objects
	//static std::vector<CustomObject3D *> asteroids;	// Asteroid objects
	static std::vector<Asteroid *> asteroids;	// Asteroid objects
	
	static Light *light_o1;						// Omnidirectional light1
	static Light *light_o2;						// Omnidirectional light2
	static Light *light_s1;						// Spot light1
	static Light *light_s2;						// Spot light2

	static int selectedObject;					// Selected object id
	static int selectedIndex;					// Selected index

	static int cameraType;						// Type of rendered camera
};