#include "HeadersAndDefines.h"
#include "WorldDrawer.h"
#include "camera.h"

float angle=0;

bool WorldDrawer::animation = true;
bool WorldDrawer::keyStates[256];
bool WorldDrawer::keySpecialStates[256];

unsigned int WorldDrawer::tick = 0;
Camera WorldDrawer::camera;

//add
void WorldDrawer::init(){

	camera.init();
	tick = glutGet(GLUT_ELAPSED_TIME);
}

// Is called in glut main loop by the system on idle
void WorldDrawer::onIdle(){	//per frame
	keyOperations();			// Operations for buffered keys
	
	
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
	
	// Arrow keys rotate the entire cube
	float rotateStep = 2.f;

	if (keySpecialStates[KEY_UP])			// Rotate cube up
	{
		//std::cerr << "UP was pressed\n";
		viewAngleY -= rotateStep;
		camera.rotateFPS_OX(-0.05);
	}
	if (keySpecialStates[KEY_DOWN])			// Rotate cube down
	{
		//std::cerr << "DOWN was pressed\n";
		viewAngleY += rotateStep;
		camera.rotateFPS_OX(0.05);
	}
	if (keySpecialStates[KEY_LEFT])			// Rotate cube left
	{
		//std::cerr << "LEFT was pressed\n";
		viewAngleX -= rotateStep;
		camera.rotateFPS_OY(-0.05);
	}
	if (keySpecialStates[KEY_RIGHT])		// Rotate cube right
	{
		//std::cerr << "RIGHT was pressed\n";
		viewAngleX += rotateStep;
		camera.rotateFPS_OY(0.05);
	}

	// Move the cube forwards and backwards
	float eyeDistanceStep = 1.f;

	if (keyStates['['])
	{
		//std::cerr << "[ was pressed\n";
		eyeDistance -= eyeDistanceStep;		// Move closer to the viewer
	}
	if (keyStates[']'])
	{
		//std::cerr << "] was pressed\n";
		eyeDistance += eyeDistanceStep;		// Move farther from the viewer
	}

	if (keyStates['w'])
	{
		camera.translate_Forward(0.5);
	}
	if (keyStates['s'])
	{
		camera.translate_Forward(-0.5);
	}
	if (keyStates['a'])
	{
		camera.translate_Right(-0.5);
	}
	if (keyStates['d'])
	{
		camera.translate_Right(0.5);
	}
	/*
	case 'a':
		camera.rotateFPS_OY(-0.1);
		break;
	case 't':
		camera.translate_Up(0.5);
		break;
	case 'g':
		camera.translate_Up(-0.5);
		break;
	case 'd':
		camera.rotateFPS_OY(0.1);
		break;
	case 'z':
		camera.rotateFPS_OX(0.1);
		break;
	case 'x':
		camera.rotateFPS_OX(-0.1);
		break;
	case 'v':
		camera.rotateFPS_OZ(0.1);
		break;
	case 'b':
		camera.rotateFPS_OZ(-0.1);
		break;

	case 'q':
		camera.rotateTPS_OY(-0.1,10);
		break;
	case 'e':
		camera.rotateTPS_OY(0.1,10);
		break;

	case 'n':
		camera.rotateTPS_OX(-0.1, 10);
		break;
	case 'm':
		camera.rotateTPS_OX(0.1, 10);
		break;

	case 'k':
		camera.rotateTPS_OZ(-0.1, 10);
		break;
	case 'l':
		camera.rotateTPS_OZ(0.1, 10);
		break;*/

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
		viewAngleX += (x - mousePosX);
		viewAngleY += (y - mousePosY);
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

// Callback for mouse scroll (wheel)
void WorldDrawer::mouseWheelCallbackFunction(int wheel, int direction, int x, int y)
{
	float eyeDistanceStep = 2.f;
	eyeDistance += eyeDistanceStep * (-direction);
}

int main(int argc, char *argv[]){
	WorldDrawer wd(argc,argv,600,600,200,100,std::string("Tema 3: Labyrinth"));
	wd.init();
	wd.run();

	return 0;
}