#include "HeadersAndDefines.h"
#include "WorldDrawer.h"
#include "camera.h"
#include "Labyrinth.h"

#include "Point2d.h"

bool WorldDrawer::animation = true;
bool WorldDrawer::keyStates[256];
bool WorldDrawer::keySpecialStates[256];

unsigned int WorldDrawer::tick = 0;
Camera WorldDrawer::camera(MODE_TPS);
Labyrinth WorldDrawer::labyrinth(10);

//add
void WorldDrawer::init(){

	// Init the labyrinth and set up camera
	labyrinth.init();

	Point2d portal = labyrinth.generateRandomPosition();
	labyrinth.setPortal(portal);
	
	Point2d player = labyrinth.generateRandomPosition();
	labyrinth.setPlayerPos(player);

	distanceToTop = (labyrinth.size * 2.f + 1) * 3.f;
	camera.init();
	float distx = (player.x - (labyrinth.size * 2 + 1) / 2) * 3.f;
	float disty = (player.y - (labyrinth.size * 2 + 1) / 2) * 3.f;
	if (camera.mode == MODE_TPS)
		camera.position = Vector3D(disty - (camera.forward * distanceToTPSTarget).x, 0.f, distx - (camera.forward * distanceToTPSTarget).z);
	else if (camera.mode == MODE_FPS)
		camera.position = Vector3D(disty, 0.f, distx);
	else if (camera.mode == MODE_TOP)
		camera.position = Vector3D(disty - (camera.forward * distanceToTop).x, 0.f, distx - (camera.forward * distanceToTop).z);


	if (camera.mode == MODE_TPS)
		camera.rotateTPS_OX(float(M_PI_4 / 2), distanceToTPSTarget);
	else if (camera.mode == MODE_TOP)
		camera.rotateTPS_OX(float(M_PI), distanceToTop);
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

	if (camera.mode == MODE_FPS)
	{
		if (keySpecialStates[KEY_UP])			// Rotate FPS up
		{
			camera.rotateFPS_OX(-rotateStep);
		}
		if (keySpecialStates[KEY_DOWN])			// Rotate FPS down
		{
			camera.rotateFPS_OX(rotateStep);
		}
		if (keySpecialStates[KEY_LEFT])			// Rotate FPS left
		{
			camera.rotateFPS_OY(-rotateStep);
		}
		if (keySpecialStates[KEY_RIGHT])		// Rotate FPS right
		{
			camera.rotateFPS_OY(rotateStep);
		}
	}
	else if (camera.mode == MODE_TPS)
	{
		if (keySpecialStates[KEY_UP])					// Rotate TPS up
		{
			camera.rotateTPS_OX(-rotateStep, distanceToTPSTarget);
		}
		if (keySpecialStates[KEY_DOWN])					// Rotate TPS down
		{
			camera.rotateTPS_OX(rotateStep, distanceToTPSTarget);
		}
		if (keySpecialStates[KEY_LEFT])					// Rotate TPS left
		{
			camera.rotateTPS_OY(-rotateStep, distanceToTPSTarget);
		}
		if (keySpecialStates[KEY_RIGHT])				// Rotate TPS right
		{
			camera.rotateTPS_OY(rotateStep, distanceToTPSTarget);
		}
	}
	else if (camera.mode == MODE_TOP)
	{
		if (keySpecialStates[KEY_LEFT])					// Rotate left
		{
			camera.rotateTPS_OY(-rotateStep, distanceToTop);
		}
		if (keySpecialStates[KEY_RIGHT])				// Rotate right
		{
			camera.rotateTPS_OY(rotateStep, distanceToTop);
		}
	}

	float eyeDistanceStep = 1.f;

	// Zoom closer
	if (keyStates['['])
	{
		eyeDistance -= eyeDistanceStep;		// Move closer to the viewer
		if (camera.mode == MODE_TPS && distanceToTPSTarget - zoomSensivity > 0)
		{
			distanceToTPSTarget -= zoomSensivity;
			camera.translate_ForwardFree(zoomSensivity);
		}
		else if (camera.mode == MODE_TOP && distanceToTop - zoomSensivity * 20 > 0)
		{
			distanceToTop -= zoomSensivity * 20;
			camera.translate_ForwardFree(zoomSensivity * 20);
		}
	}
	if (keyStates[']'])
	{
		eyeDistance += eyeDistanceStep;		// Move farther from the viewer
		if (camera.mode == MODE_TPS)
		{
			distanceToTPSTarget += zoomSensivity;
			camera.translate_ForwardFree(-zoomSensivity);
		}
		else if (camera.mode == MODE_TOP)
		{
			distanceToTop += zoomSensivity * 20;
			camera.translate_ForwardFree(-zoomSensivity * 20);
		}
	}

	if (keyStates['w'])						// Move forward
	{
		camera.translate_Forward(moveStep);

		// Check colision
		
		Vector3D newPos = getPlayerPosition();
		std::vector<Point2d> neighbours = labyrinth.getNeighbours(labyrinth.playerPos);

		bool updatedCell = labyrinth.updateCell(neighbours, newPos);

		if (labyrinth.foundPortal())
		{
			Sleep(1000);
			int mode = camera.mode;
			switchCameraMode(MODE_FPS);
			init();
			switchCameraMode(mode);
		}
		if (!updatedCell)
		{
			for (unsigned int i = 0; i < neighbours.size(); ++i)
				if (labyrinth.isColision(neighbours[i], newPos))
				{
					camera.translate_Forward(-moveStep);
				}
		}

	}
	if (keyStates['s'])						// Move backwards
	{
		camera.translate_Forward(-moveStep);

		// Check colision
		Vector3D newPos = getPlayerPosition();
		std::vector<Point2d> neighbours = labyrinth.getNeighbours(labyrinth.playerPos);
		bool updatedCell = labyrinth.updateCell(neighbours, newPos);

		if (labyrinth.foundPortal())
		{
			Sleep(1000);
			int mode = camera.mode;
			switchCameraMode(MODE_FPS);
			init();
			switchCameraMode(mode);
		}
		if (!updatedCell)
		{
			for (unsigned int i = 0; i < neighbours.size(); ++i)
				if (labyrinth.isColision(neighbours[i], newPos))
				{
					camera.translate_Forward(moveStep);
				}
		}
	}
	if (keyStates['a'])						// Move left
	{
		camera.translate_Right(-moveStep);

		// Check colision
		Vector3D newPos = getPlayerPosition();
		std::vector<Point2d> neighbours = labyrinth.getNeighbours(labyrinth.playerPos);
		bool updatedCell = labyrinth.updateCell(neighbours, newPos);

		if (labyrinth.foundPortal())
		{
			Sleep(1000);
			int mode = camera.mode;
			switchCameraMode(MODE_FPS);
			init();
			switchCameraMode(mode);
		}
		if (!updatedCell)
		{
			for (unsigned int i = 0; i < neighbours.size(); ++i)
				if (labyrinth.isColision(neighbours[i], newPos))
				{
					camera.translate_Right(moveStep);
				}
		}
	}
	if (keyStates['d'])						// Move right
	{
		camera.translate_Right(moveStep);

		// Check colision
		Vector3D newPos = getPlayerPosition();
		std::vector<Point2d> neighbours = labyrinth.getNeighbours(labyrinth.playerPos);
		bool updatedCell = labyrinth.updateCell(neighbours, newPos);

		if (labyrinth.foundPortal())
		{
			Sleep(1000);
			int mode = camera.mode;
			switchCameraMode(MODE_FPS);
			init();
			switchCameraMode(mode);
		}
		if (!updatedCell)
		{
			for (unsigned int i = 0; i < neighbours.size(); ++i)
				if (labyrinth.isColision(neighbours[i], newPos))
				{
					camera.translate_Right(-moveStep);
				}
		}
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
		viewAngleX += (y - mousePosY) / mouseSensivity;
		viewAngleY += (x - mousePosX) / mouseSensivity;
		mousePosX = float(x);
		mousePosY = float(y);
	}
	if (mouseRightState == true)		// Make zoom in/out if right is clicked and moved
	{
		eyeDistance -= (y - mousePosY) * eyeDistanceStep;
		mousePosY = float (y);
	}
}

// Execute mouse rotations
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
	if (camera.mode == MODE_TPS && distanceToTPSTarget + zoomSensivity * 20 * (-direction) > 0)
	{
		distanceToTPSTarget += zoomSensivity * 20 * (-direction);
		camera.translate_ForwardFree(-zoomSensivity * 20 * (-direction));
	}
	else if (camera.mode == MODE_TOP && distanceToTop + zoomSensivity * 50 * (-direction) > 0)
	{
		distanceToTop += zoomSensivity * 50 * (-direction);
		camera.translate_ForwardFree(-zoomSensivity * 50 * (-direction));
	}
}

// Switches the camera mode
void WorldDrawer::switchCameraMode(int mode)
{
	if (camera.mode == MODE_FPS && mode == MODE_TPS)
	{
		camera.rotateFPS_OX(float(ANGLE_LIMIT * 2));
		camera.rotateFPS_OX(float(-ANGLE_LIMIT + camera.angleTpsX));
		camera.translate_ForwardFree(-distanceToTPSTarget);
	}
	else if (camera.mode == MODE_FPS && mode == MODE_TOP)
	{
		camera.rotateFPS_OX(float(ANGLE_LIMIT * 2));
		camera.translate_ForwardFree(-distanceToTop);
	}
	else if (camera.mode == MODE_TPS && mode == MODE_FPS)
	{
		camera.angleTpsX = camera.getAngleX();
		camera.translate_ForwardFree(distanceToTPSTarget);
		camera.rotateFPS_OX(float(ANGLE_LIMIT * 2));
		camera.rotateFPS_OX(float(-ANGLE_LIMIT));
	}
	else if (camera.mode == MODE_TPS && mode == MODE_TOP)
	{
		camera.angleTpsX = camera.getAngleX();
		camera.translate_ForwardFree(distanceToTPSTarget);
		camera.rotateFPS_OX(float(ANGLE_LIMIT * 2));
		camera.translate_ForwardFree(-distanceToTop);
	}
	else if (camera.mode == MODE_TOP && mode == MODE_FPS)
	{
		camera.translate_ForwardFree(distanceToTop);
		camera.rotateFPS_OX(float(-ANGLE_LIMIT));
	}
	else if (camera.mode == MODE_TOP && mode == MODE_TPS)
	{
		camera.translate_ForwardFree(distanceToTop);
		camera.rotateFPS_OX(float(-ANGLE_LIMIT + camera.angleTpsX));
		camera.translate_ForwardFree(-distanceToTPSTarget);
	}
	camera.mode = mode;
}

// Gets the position of the player in world space
Vector3D WorldDrawer::getPlayerPosition()
{
	if (camera.mode == MODE_FPS)
		return camera.position;
	else
	{
		int mode = camera.mode;
		switchCameraMode(MODE_FPS);
		Vector3D temp(camera.position);
		switchCameraMode(mode);
		return temp;
	}
}

int main(int argc, char *argv[]){
	srand((unsigned int)time(0));

	WorldDrawer wd(argc, argv, 800, 600, 200, 200, std::string("Tema 3: Labyrinth"));
	wd.init();
	wd.run();
	
	return 0;
}