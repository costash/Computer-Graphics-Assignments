#include "HeadersAndDefines.h"
#include "WorldDrawer.h"
#include "camera.h"
#include "Labyrinth.h"

#include "Point2d.h"

bool WorldDrawer::animation = true;
bool WorldDrawer::keyStates[256];
bool WorldDrawer::keySpecialStates[256];

unsigned int WorldDrawer::tick = 0;
Camera WorldDrawer::camera;

//add
void WorldDrawer::init(){

	Labyrinth *l = new Labyrinth(31);
	l->init();
	std::cerr << *l;
	l->generateNewMaze();
	std::cerr << "new\n\n" << *l;

	camera.init();
	tick = glutGet(GLUT_ELAPSED_TIME);
}

// Is called in glut main loop by the system on idle
void WorldDrawer::onIdle(){	//per frame
	keyOperations();			// Operations for buffered keys
	mouseRotations();
	
	if(animation){
		// Do nothing here
		angle = angle+1;
	
		if(angle > 360) angle = angle-360;
	}
}

// All key events are processed here
void WorldDrawer::keyOperations()
{
	if (keyStates[KEY_ESC])			// On Escape, program exits
		glutExit();
	
	float rotateStep = 0.04f;
	float moveStep = 0.25f;

	if (keySpecialStates[KEY_UP])			// Rotate FPS up
	{
		//std::cerr << "UP was pressed\n";
		//viewAngleX -= rotateStep;
		camera.rotateFPS_OX(-rotateStep);
	}
	if (keySpecialStates[KEY_DOWN])			// Rotate FPS down
	{
		//std::cerr << "DOWN was pressed\n";
		//viewAngleX += rotateStep;
		camera.rotateFPS_OX(rotateStep);
	}
	if (keySpecialStates[KEY_LEFT])			// Rotate FPS left
	{
		//std::cerr << "LEFT was pressed\n";
		//viewAngleY -= rotateStep;
		camera.rotateFPS_OY(-rotateStep);
	}
	if (keySpecialStates[KEY_RIGHT])		// Rotate FPS right
	{
		//std::cerr << "RIGHT was pressed\n";
		//viewAngleY += rotateStep;
		camera.rotateFPS_OY(rotateStep);
	}

	if (keyStates['i'])					// Rotate TPS up
	{
		//viewAngleTpsX -= rotateStep;
		camera.rotateTPS_OX(-rotateStep, distanceToTPSTarget);
	}
	if (keyStates['k'])					// Rotate TPS down
	{
		//viewAngleTpsX += rotateStep;
		camera.rotateTPS_OX(rotateStep, distanceToTPSTarget);
	}
	if (keyStates['j'])						// Rotate TPS left
	{
		//viewAngleTpsY -= rotateStep;
		camera.rotateTPS_OY(-rotateStep, distanceToTPSTarget);
	}
	if (keyStates['l'])						// Rotate TPS right
	{
		//viewAngleTpsY += rotateStep;
		camera.rotateTPS_OY(rotateStep, distanceToTPSTarget);
	}

	// Move the cube forwards and backwards
	float eyeDistanceStep = 1.f;

	if (keyStates['['])
	{
		//std::cerr << "[ was pressed\n";
		eyeDistance -= eyeDistanceStep;		// Move closer to the viewer
		if (camera.mode == MODE_TPS)
		{
			distanceToTPSTarget -= zoomSensivity;
			camera.translate_ForwardFree(zoomSensivity);
		}
	}
	if (keyStates[']'])
	{
		//std::cerr << "] was pressed\n";
		eyeDistance += eyeDistanceStep;		// Move farther from the viewer
		if (camera.mode == MODE_TPS)
		{
			distanceToTPSTarget += zoomSensivity;
			camera.translate_ForwardFree(-zoomSensivity);
		}
	}

	if (keyStates['w'])
	{
		camera.translate_Forward(moveStep);
	}
	if (keyStates['s'])
	{
		camera.translate_Forward(-moveStep);
	}
	if (keyStates['a'])
	{
		camera.translate_Right(-moveStep);
	}
	if (keyStates['d'])
	{
		camera.translate_Right(moveStep);
	}
}

// Callback function for mouse actions
void WorldDrawer::mouseCallbackFunction(int button, int state, int x, int y)
{
	mousePosX = float (x);
	mousePosY = float (y);
	if (button == MOUSE_LEFT)			// Buffer left clicks
	{
		if (state == GLUT_DOWN)
			mouseLeftState = true;
		else if (state == GLUT_UP)
			mouseLeftState = false;
	}
	else if (button == MOUSE_RIGHT)		// Buffer right clicks
	{
		if (state == GLUT_DOWN)
			mouseRightState = true;
		else if (state == GLUT_UP)
			mouseRightState = false;
	}
}

// Callback for mouse movement
void WorldDrawer::mouseMotionCallbackFunction(int x, int y)
{
	float eyeDistanceStep = 0.2f;
	if (mouseLeftState == true)			// Make rotation if left is clicked and moved mouse
	{
		//std::cerr << "(" << mousePosX << "," << mousePosY << ") MouseLeft ";
		viewAngleX += (y - mousePosY) / mouseSensivity;
		viewAngleY += (x - mousePosX) / mouseSensivity;
		mousePosX = float(x);
		mousePosY = float(y);
	}
	if (mouseRightState == true)		// Make zoom in/out if right is clicked and moved
	{
		//std::cerr << "(" << mousePosX << "," << mousePosY << ") MouseRight ";
		eyeDistance -= (y - mousePosY) * eyeDistanceStep;
		mousePosY = float (y);
	}
}

void WorldDrawer::mouseRotations()
{
	if (camera.mode == MODE_FPS)
	{
		camera.rotateFPS_OX(viewAngleX);
		camera.rotateFPS_OY(viewAngleY);
		viewAngleX = viewAngleY = 0.f;
	}
	else if (camera.mode == MODE_TPS)
	{
		camera.rotateTPS_OX(viewAngleX, distanceToTPSTarget);
		camera.rotateTPS_OY(viewAngleY, distanceToTPSTarget);
		viewAngleX = viewAngleY = 0.f;
	}
}

// Callback for mouse scroll (wheel)
void WorldDrawer::mouseWheelCallbackFunction(int wheel, int direction, int x, int y)
{
	float eyeDistanceStep = 2.f;
	eyeDistance += eyeDistanceStep * (-direction);
	if (camera.mode == MODE_TPS)
	{
		distanceToTPSTarget += zoomSensivity * 20 * (-direction);
		camera.translate_ForwardFree(-zoomSensivity * 20 * (-direction));
	}
}

int main(int argc, char *argv[]){
	srand((unsigned int)time(0));

	WorldDrawer wd(argc,argv,600,600,200,100,std::string("Tema 3: Labyrinth"));
	wd.init();
	wd.run();
	
	return 0;
}